package il.co.ilrd.collections;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class WaitableQueue<E> {
	private Queue<E> priorityQueue;
	private Object monitor = new Object();
	
	public WaitableQueue() {
		priorityQueue = new PriorityQueue<>();
	}
	
	public WaitableQueue(Comparator<E>) {
		
	}
}
