package il.co.ilrd.design_pattern.thread_pool;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import javax.naming.spi.DirStateFactory.Result;

import org.junit.internal.runners.statements.RunAfters;

import il.co.ilrd.collections.WaitableQueue;

public class ThreadPool {
	
	private WaitableQueue<Task<?>> enqueQueue = new WaitableQueue<>();
	private WaitableQueue<Task<?>> dequeQueue = enqueQueue;
	private volatile int numOfThreads = 0;
	
	private Semaphore semaphorePause = new Semaphore(0);
	private Semaphore semaphoreShutdown = new Semaphore(0);
	
	public enum Priority{
		LOW,
		MEDIUM,
		HIGH;
	}
	
	private class Task<V> implements Comparable<V>{
		int priority;
		FutureTask futureTask;
		
		public Task(Runnable runnableTask, Priority priority, V value) {
			this.priority = priority.ordinal(); //set enum value
			this.futureTask = new FutureTask();
		}
		
		public Task(Runnable runnableTask, int priority, boolean isRunning) {
			this.priority = priority;
			
		}
		
		public Task(Callable c, Priority priority) {
			this.priority = priority.ordinal();
		}
		
		@Override
		public int compareTo(V o) {
			return 0;
		}
		
		private class FutureTask implements Future<V>{
			V result = null;
			Callable<V> callable = null;
			boolean isRunning = true;
			
			public FutureTask(Runnable runnableTask) {
				
			}
			
			public FutureTask(Callable<V> callableTask) {
				
			}
			
			public FutureTask(Runnable runnableTask, V value, boolean isRunning) {
				
			}
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public V get() throws InterruptedException, ExecutionException {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public V get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public boolean isCancelled() {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public boolean isDone() {
				// TODO Auto-generated method stub
				return false;
			}
			
		}
	}
	
	class WorkingThread implements Runnable{
		private boolean isRunning = true;

		@Override
		public void run() {
			/*while(isRunning) {
				
			}*/
		}
	}
	
	class TerminatedThread implements Runnable{

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
		return null;
	}

	public <T>Future<T> submit(Runnable r, Comparator<Callable<T>> priority){
		return null;
	}
	
	public <T>Future<T> submit(Runnable r, Comparator<Callable<T>> priority, T value){
		return null;
	}
	
	
	public <T>Future<T> submit(Callable<T> c, Comparator<Callable<T>> priority){
		return null;
	}
	
	public void setNumOfThreads(int newNumOfThreads) {
		if(newNumOfThreads > numOfThreads) {
			for (int i = 0; i < newNumOfThreads - numOfThreads; ++i) {
					threadList.push(new WorkingThread());
					new Thread(threadList.get(0)).start();
			}
		}
		else{
			for (int i = 0; i < numOfThreads - newNumOfThreads; ++i) {
				//taskQueue.enqueue(new Task<Runnable>(new TerminatedThread(), 4));
			}
		}
		numOfThreads = newNumOfThreads;
	}
	
	public void pause() {
		for (int i = 0; i < numOfThreads; ++i) {
			
		}
	}
	
	public void resume() {
		semaphorePause.release(numOfThreads);
	}
	
	public void shutDown() {
		
	}
	
	public void awaitTermination() {
		try {
			semaphoreShutdown.acquire(numOfThreads);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
}
