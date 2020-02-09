package il.co.ilrd.collections;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.TimeUnit;

public class WaitableQueue<E> {
	private Queue<E> priorityQueue;
	private Object monitor = new Object();
	
	public WaitableQueue(){
		priorityQueue = new PriorityQueue<>();
	}
	
	public WaitableQueue(Comparator<E> comparator) {
		priorityQueue = new PriorityQueue<>(10, comparator);
	}
	
	public boolean isEmpty() {
		return priorityQueue.isEmpty();
	}
	
	public void enqueue(E task) {
		synchronized (monitor) {
			priorityQueue.add(task);
			monitor.notify();
		}
	}
	
	public E dequeue() {
		synchronized (monitor) {
			try {
				while(priorityQueue.isEmpty()) {					
					monitor.wait();
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		return priorityQueue.poll();
		}
	}
	
	
	public E dequeueTimeout(long time, TimeUnit timeUnit) {
		synchronized (monitor) {
			while(priorityQueue.isEmpty()) {
				try {
					timeUnit.timedWait(monitor, time);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		return priorityQueue.poll();
		}
	}
}
