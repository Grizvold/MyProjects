package il.co.ilrd.design_pattern.thread_pool;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.collections.WaitableQueue;

public class ThreadPool {
	
	private WaitableQueue<Task<?>> submitQueue = new WaitableQueue<>();
	private WaitableQueue<Task<?>> managementQueue = submitQueue;
	private volatile int numOfThreads = 0;
	private boolean isPaused = false;
	private Object monitorObject = new Object();
	
	private Semaphore semaphorePause = new Semaphore(0);
	private Semaphore semaphoreShutdown = new Semaphore(0);
	
	public enum Priority{
		LOW,
		MEDIUM,
		HIGH;
	}
	
	private class Task<V> implements Comparable<Task<V>>{
		private int priority = 0;
		private FutureTask<V> futureTask = null; 
		private boolean isRunning = true;
		
		public Task(Callable<V> callableTask, Priority priority) {
			this.priority = priority.ordinal();
			futureTask = new FutureTask<V>(callableTask);
		}
		
		public Task(Runnable runnableTask, int priority, boolean isRunning) {
			this.isRunning = isRunning;
			this.priority = priority;
			futureTask = new FutureTask<V>(Executors.callable(runnableTask, null));
		}
		
		
		@Override
		public int compareTo(Task<V> compareItem) {
			return compareItem.priority - this.priority;
		}
		
		private class FutureTask<U> implements Future<U>{
			private U result = null;
			private boolean isDone = false;
			private boolean isCanceled = false;
			private Callable<U> callable = null;
			
			public FutureTask(Callable<U> callableTask) {
				callable = callableTask;
			}
			
			public boolean run() {
				try {
					result = callable.call();
					synchronized (monitorObject) {
						monitorObject.notify();
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
				isDone = true;
				return isRunning;
			}
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				if(managementQueue.remove(Task.this)) {
					isCanceled = true;
					isDone = true;
					synchronized (monitorObject) {
						monitorObject.notify();
					}
				}
				return isCanceled;
			}

			@Override
			public U get() throws InterruptedException, ExecutionException {
				synchronized (monitorObject) {
					if (!isDone) {
						monitorObject.wait();
					}
				}
				return result;
			}

			@Override
			public U get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				synchronized (monitorObject) {
					if (!isDone) {
						unit.timedWait(monitorObject, timeout);
					}
				}
				return result;
			}

			@Override
			public boolean isCancelled() {
				return isCanceled;
			}

			@Override
			public boolean isDone() {
				return isDone;
			}
			
		}
	}
	
	private class WorkingThread implements Runnable{
		private boolean isRunning = true;

		@Override
		public void run() {
			while(isRunning) {
				isRunning = managementQueue.dequeue().futureTask.run();
			}
		}
	}
	
	public ThreadPool(int numOfThreads) {
		this.numOfThreads = numOfThreads;
		
		for (int i = 0; i < numOfThreads; ++i) {
			new Thread(new WorkingThread()).start();
		}
	}
	
	public <T>Future<T> submit(Callable<T> c){
		Task<T> task = new Task<>(c, Priority.MEDIUM);
		try {
			submitQueue.enqueue(task);
			
		} catch (NullPointerException e) {
			throw new RejectedExecutionException();
		}
		
		return task.futureTask;
	}

	public <T>Future<T> submit(Runnable r, Priority priority){
		Task<T> task = new Task<>(Executors.callable(r, null), priority);
		try {
			submitQueue.enqueue(task);
			
		} catch (NullPointerException e) {
			throw new RejectedExecutionException();
		}
		
		return task.futureTask;
	}
	
	public <T>Future<T> submit(Runnable r, Priority priority, T value){
		Task<T> task = new Task<>(Executors.callable(r, value), priority);
		try {
			submitQueue.enqueue(task);
			
		} catch (NullPointerException e) {
			throw new RejectedExecutionException();
		}
		
		return task.futureTask;
	}
	
	
	public <T>Future<T> submit(Callable<T> c, Priority priority){
		Task<T> task = new Task<>(c, priority);
		try {
			submitQueue.enqueue(task);
			
		} catch (NullPointerException e) {
			throw new RejectedExecutionException();
		}
		
		return task.futureTask;
	}
	
	public void setNumOfThreads(int newNumOfThreads) {
		if(!isPaused) {			
			if(newNumOfThreads > numOfThreads) {
				for (int i = numOfThreads; i < newNumOfThreads; ++i) {
					new Thread(new WorkingThread()).start();
				}
			}
			else{
				for (int i = newNumOfThreads; i < numOfThreads; ++i) {
					submitQueue.enqueue(new Task<Runnable>(()->{}, 4, false));
				}
			}
			numOfThreads = newNumOfThreads;
		}
		else {
			throw new IllegalStateException();
		}
	}
	
	public void pause() {
		Task<Runnable> pauseTask = new Task<>(()-> {try {
			semaphorePause.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}}, 4, true);
		
		for (int i = 0; i < numOfThreads; ++i) {
			submitQueue.enqueue(pauseTask);
		}
		isPaused = true;
	}
	
	public void resume() {
		semaphorePause.release(numOfThreads);
		isPaused = false;
	}
	
	public void shutDown() {
		if (isPaused) {
			resume();
		}
		submitQueue = null;
		for (int i = 0; i < numOfThreads; ++i) {			
			managementQueue.enqueue(new Task<Runnable>(()->{semaphoreShutdown.release();}, -1, false));
		}
	}
	
	public void awaitTermination() {
		try {
			semaphoreShutdown.acquire(numOfThreads);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
}
