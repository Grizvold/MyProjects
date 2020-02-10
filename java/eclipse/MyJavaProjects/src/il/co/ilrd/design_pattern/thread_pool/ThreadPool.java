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
	
	private Semaphore semaphorePause = new Semaphore(0);
	private Semaphore semaphoreShutdown = new Semaphore(0);
	
	public enum Priority{
		LOW,
		MEDIUM,
		HIGH;
	}
	
	private class Task<V> implements Comparable<Task<V>>{
		int priority;
		FutureTask<V> futureTask;
		
		public Task(Callable<V> callableTask, Priority priority) {
			this.priority = priority.ordinal();
			futureTask = new FutureTask<V>(callableTask);
		}

		public Task(Runnable runnableTask, Priority priority, V value) {
			this.priority = priority.ordinal(); //set enum value
			futureTask = new FutureTask<V>(runnableTask, value);
		}
		
		public Task(Runnable runnableTask, int priority, boolean isRunning) {
			this.priority = priority;
			futureTask = new FutureTask<V>(runnableTask, null, isRunning);
		}
		
		
		@Override
		public int compareTo(Task<V> compareItem) {
			return compareItem.priority - this.priority;
		}
		
		private class FutureTask<U> implements Future<U>{
			U result = null;
			boolean isRunning = true;
			boolean isDone = false;
			boolean isCanceled = false;
			Callable<U> callable = null;
			
			public FutureTask(Callable<U> callableTask) {
				callable = callableTask;
			}
			
			public FutureTask(Runnable runnableTask, U value) {
				callable = Executors.callable(runnableTask, value);
			}
			
			
			public FutureTask(Runnable runnableTask, U value, boolean isRunning) {
				callable = Executors.callable(runnableTask, value);
				this.isRunning = isRunning;
			}
			
			public boolean run() {
				try {
					result = callable.call();
					synchronized (callable) {
						callable.notify();
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
					return true;
				}
				return isCanceled;
			}

			@Override
			public U get() throws InterruptedException, ExecutionException {
				synchronized (callable) {
					if (!isDone) {
						callable.wait();
					}
				}
				return result;
			}

			@Override
			public U get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				synchronized (callable) {
					if (!isDone) {
						unit.timedWait(callable, timeout);
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
	
	class WorkingThread implements Runnable{
		private boolean isRunning = true;

		@Override
		public void run() {
			while(isRunning) {
				isRunning = managementQueue.dequeue().futureTask.run();
			}
		}
	}
	
	class ShutDownThread implements Runnable{

		@Override
		public void run() {
			semaphoreShutdown.release();
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
		Task<T> task = new Task<>(r, priority, null);
		try {
			submitQueue.enqueue(task);
			
		} catch (NullPointerException e) {
			throw new RejectedExecutionException();
		}
		
		return task.futureTask;
	}
	
	public <T>Future<T> submit(Runnable r, Priority priority, T value){
		Task<T> task = new Task<>(r, priority, value);
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
		if(newNumOfThreads > numOfThreads) {
			for (int i = 0; i < newNumOfThreads - numOfThreads; ++i) {
				new Thread(new WorkingThread()).start();
			}
		}
		else{
			for (int i = 0; i < numOfThreads - newNumOfThreads; ++i) {
				submitQueue.enqueue(new Task<Runnable>(()->{},4 ,false));
			}
		}
		numOfThreads = newNumOfThreads;
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
	}
	
	public void resume() {
		semaphorePause.release(numOfThreads);
	}
	
	public void shutDown() {
		submitQueue = null;
		for (int i = 0; i < numOfThreads; ++i) {			
			managementQueue.enqueue(new Task<Runnable>(new ShutDownThread(), 4, false));
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
