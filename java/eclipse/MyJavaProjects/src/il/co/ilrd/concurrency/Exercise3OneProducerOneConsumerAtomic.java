package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicBoolean;

public class Exercise3OneProducerOneConsumerAtomic {
	
	static AtomicBoolean threadFlag = new AtomicBoolean(true);
	
	public static void main(String[] args) {
		Thread producerThread = new Thread(new Ex3RunnableProducer());
		Thread consumerThread = new Thread(new Ex3RunnableConsumer());
		
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

class Ex3RunnableProducer implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{			
			if(Exercise3OneProducerOneConsumerAtomic.threadFlag.get())
			{
				System.out.println("Ping producer");
				Exercise3OneProducerOneConsumerAtomic.threadFlag.set(false);
			}				
		}
	}
}

class Ex3RunnableConsumer implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
			if(!Exercise3OneProducerOneConsumerAtomic.threadFlag.get())
			{
				System.out.println("Pong consumer");
				Exercise3OneProducerOneConsumerAtomic.threadFlag.set(true);
			}
		}
	}
}