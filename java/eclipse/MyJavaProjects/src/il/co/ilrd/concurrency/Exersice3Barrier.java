package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class Exersice3Barrier {
	static Semaphore semaphore = new Semaphore(0);
	static Object monitorObject = new Object();
	static int sharedInteger = 0;
	static int numberOfConsumers = 3;
	
	public static void main(String[] args) {
		Thread[] consumersThreads = new Thread[numberOfConsumers];
		Thread producerThread = new Thread(new Ex3BarrierProducer());

		
		for (int i = 0; i < numberOfConsumers; ++i) {
			consumersThreads[i] = new Thread(new Ex3BarrierComsumer());
			consumersThreads[i].start();
		}
		
		producerThread.start();
	}
}


class Ex3BarrierProducer implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
				try {
					for (int i = 0; i < Exersice3Barrier.numberOfConsumers; ++i) {						
						Exersice3Barrier.semaphore.acquire(); 
					}
					Exersice3Barrier.sharedInteger++;
					
				} catch (Exception e) {
				}
				synchronized (Exersice3Barrier.monitorObject) {
					Exersice3Barrier.monitorObject.notifyAll();
				}
		}
	}
}

class Ex3BarrierComsumer implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
			synchronized (Exersice3Barrier.monitorObject) {
				try {
					Exersice3Barrier.semaphore.release();
					Exersice3Barrier.monitorObject.wait();
					System.out.println(Exersice3Barrier.sharedInteger);
				} catch (Exception e) {
					
				}
			}
		}
	}
}
