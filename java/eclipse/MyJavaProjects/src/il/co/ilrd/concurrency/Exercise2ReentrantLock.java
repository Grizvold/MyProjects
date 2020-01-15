package il.co.ilrd.concurrency;

import java.util.concurrent.locks.ReentrantLock;

public class Exercise2ReentrantLock{
	
	static ReentrantLock reentrantLock = new ReentrantLock();
	
	public static int counter = 0;
	
	public static void main(String[] args) {
		Exercise2ReentrantLock exercise2 = new Exercise2ReentrantLock();
		
		exercise2.startExecution();
		System.out.println("Counter Value: " + exercise2.getCounter());
	}

	public void startExecution() {
		Thread thread1 = new Thread(new RunnableThreadEx2ReentrantLock());
		Thread thread2 = new Thread(new RunnableThreadEx2ReentrantLock());
		
		long start = System.currentTimeMillis();
		thread1.start();
		thread2.start();
		
		try {
			thread1.join();
			thread2.join();
		} catch (Exception e) {
		}
		long finish = System.currentTimeMillis();

		System.out.println("Execution time: " +  (finish - start));
	}
	
	public int getCounter() {
		return counter;
	}
}

class RunnableThreadEx2ReentrantLock implements Runnable{
	@Override
	public void run() {
		for (int i = 0; i < 10000000; ++i) {
			Exercise2ReentrantLock.reentrantLock.lock();
			++Exercise2ReentrantLock.counter;
			Exercise2ReentrantLock.reentrantLock.unlock();
		}
	}
}
