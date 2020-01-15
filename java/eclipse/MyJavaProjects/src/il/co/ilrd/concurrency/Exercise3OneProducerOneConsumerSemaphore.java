package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class Exercise3OneProducerOneConsumerSemaphore {
	static Semaphore semaphore1 = new Semaphore(1);
	static Semaphore semaphore2 = new Semaphore(0);
	
	public static void main(String[] args) {
		Thread producerThread = new Thread(new Ex3RunnableProducerSema());
		Thread consumerThread = new Thread(new Ex3RunnableConsumerSema());
		
		producerThread.start();
		consumerThread.start();
		
		try {
			Thread.sleep(1000);
		} catch (Exception e) {
		}
		
		producerThread.interrupt();
		consumerThread.interrupt();
	}
}

class Ex3RunnableProducerSema implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	

			try {				
				Exercise3OneProducerOneConsumerSemaphore.semaphore1.acquire();
				System.out.println("Ping producer");
				Exercise3OneProducerOneConsumerSemaphore.semaphore2.release();
			} catch (Exception e) {
			}
			
		}
	}
}

class Ex3RunnableConsumerSema implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
			try {		
				Exercise3OneProducerOneConsumerSemaphore.semaphore2.acquire();
				System.out.println("Pong consumer");
				Exercise3OneProducerOneConsumerSemaphore.semaphore1.release();
			} catch (Exception e) {
			}
		}
	}
}