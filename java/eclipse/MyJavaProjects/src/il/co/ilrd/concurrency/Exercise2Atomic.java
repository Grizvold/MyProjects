package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicInteger;

public class Exercise2Atomic{

	static AtomicInteger counterAtomicInteger = new AtomicInteger(0);
	
	public static void main(String[] args) {
		Exercise2Atomic exercise2 = new Exercise2Atomic();
		
		exercise2.startExecution();
		System.out.println("Counter Value: " + exercise2.getCounter());
	}

	public void startExecution() {
		Thread thread1 = new Thread(new RunnableThreadEx2Atomic());
		Thread thread2 = new Thread(new RunnableThreadEx2Atomic());
		
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
		return counterAtomicInteger.get();
	}
}

class RunnableThreadEx2Atomic implements Runnable{
	@Override
	public void run() {
		for (int i = 0; i < 10000000; ++i) {
			Exercise2Atomic.counterAtomicInteger.incrementAndGet();
		}
	}
}
