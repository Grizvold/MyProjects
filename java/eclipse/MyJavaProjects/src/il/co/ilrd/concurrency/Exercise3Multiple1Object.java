package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class Exercise3Multiple1Object {
	static Semaphore ex3seSemaphore = new Semaphore(0);
	static LinkedList <Integer> linkedList = new LinkedList<Integer>();
	static Object syncObject = new Object();
	
	public static void main(String[] args) {
		int numberOfThreads = 100;
		Thread[] producersThreads = new Thread[numberOfThreads];
		Thread[] comsumersThreads = new Thread[numberOfThreads];
		
		for (int i = 0; i < numberOfThreads; ++i) {
			producersThreads[i] = new Thread(new Ex3MultipleProducer());
			comsumersThreads[i] = new Thread(new Ex3MultipleConsumer());
			
			producersThreads[i].start();
			comsumersThreads[i].start();
		}
		
		/*try {
			Thread.sleep(1000);
			
		} catch (Exception e) {
		}
		
		for (int i = 0; i < numberOfThreads; ++i) {
			producersThreads[i].interrupt();
			comsumersThreads[i].interrupt();
		}*/
	}
}

class Ex3MultipleProducer implements Runnable{
	private static int i = 0;
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
			synchronized (Exercise3Multiple1Object.syncObject) {
				Exercise3Multiple1Object.linkedList.add(i++);
				Exercise3Multiple1Object.ex3seSemaphore.release();
			}
		}
	}
}


class Ex3MultipleConsumer implements Runnable{
	@Override
	public void run() {
		while(!Thread.interrupted())
		{	
			synchronized (Exercise3Multiple1Object.syncObject) {
				//if(!Exercise3Multiple1Object.linkedList.isEmpty())
				try {
					Exercise3Multiple1Object.ex3seSemaphore.acquire();
					System.out.println(Exercise3Multiple1Object.linkedList.pop());
				} catch (InterruptedException e) {
					e.printStackTrace();
				}				
			}
		}
	}
}
