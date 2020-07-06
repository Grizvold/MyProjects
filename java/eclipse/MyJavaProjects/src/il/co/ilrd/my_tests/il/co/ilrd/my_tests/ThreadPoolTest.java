package il.co.ilrd.my_tests;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.design_pattern.thread_pool.ThreadPool;
import il.co.ilrd.design_pattern.thread_pool.ThreadPool.Priority;

public class ThreadPoolTest {
	static final int numOfLoopIterations = 40;
	static Integer counter = 1;

	public static void main(String[] args) throws InterruptedException, ExecutionException, TimeoutException {
		ThreadPool executer = new ThreadPool(3);
		List<Future<Integer>> runnableFutureArr = new ArrayList<>();
		List<Future<Integer>> callableFutureArr = new ArrayList<>();

		
		for (int i = 0; i < numOfLoopIterations; ++i) {
			runnableFutureArr.add((Future<Integer>) executer.submit(new TaskRunnable(),
																		Priority.MEDIUM,
																		++counter));
		}
		
		executer.pause();
		System.out.println("\n### 1st pause ###\n");

		
		for (int i = 0; i < numOfLoopIterations; ++i) {
			callableFutureArr.add((Future<Integer>) executer.submit(new TaskCallable(),
																		Priority.HIGH));
		}
		
		executer.resume();
		
		executer.setNumOfThreads(15);
		System.out.println("\nMAIN SLEEPING\n");
		Thread.sleep(3000);
		executer.setNumOfThreads(2);
		System.out.println("\nMAIN SLEEPING\n");
		Thread.sleep(3000);
		
		executer.pause();
		System.out.println("\n### 2nd paused ###\n");
		System.out.println("\nMAIN SLEEPING\n");
		Thread.sleep(3000);
		executer.resume();

		
		executer.setNumOfThreads(10);
		System.out.println("\nMAIN SLEEPING\n");
		Thread.sleep(3000);
		executer.setNumOfThreads(5);
		System.out.println("\nMAIN SLEEPING\n");
		Thread.sleep(6000);

		System.out.println("\n### now SHUTDOWN ###");
		executer.shutDown();
		executer.awaitTermination();
		System.out.println("\n### TERMINATED ###\n");
		Thread.sleep(4000);
		
		Iterator<Future<Integer>> iterRunnable = runnableFutureArr.iterator();
		Iterator<Future<Integer>> iterCallable = callableFutureArr.iterator();
		for (int i = 0; i < numOfLoopIterations; ++i) {
			System.out.println("runnable future = " + 
								iterRunnable.next().get(100, TimeUnit.MILLISECONDS));
			System.out.println("callable future = " + 
								iterCallable.next().get(100, TimeUnit.MILLISECONDS));
		}		
		System.out.println("\n****** FINISHED ******");
	}
	

	static class TaskRunnable implements Runnable {
		
		@Override
		public void run() {
			System.out.println(counter + " Runnable task");	
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
		
	static class TaskCallable implements Callable<Integer>{
		
		@Override
		public Integer call() throws Exception {
			System.out.println(counter + "\tCallable task");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			return ++counter;
		}
	}
}