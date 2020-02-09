package il.co.ilrd.design_pattern.thread_pool;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;

import il.co.ilrd.collections.WaitableQueue;

public class ThreadPool {
	
	private WaitableQueue<?> taskQueue = new WaitableQueue<>();
	private ArrayList<Thread> threadPool;
	private int numOfThreads;
	
	public ThreadPool(int numOfThreads) {
		
	}
	
	public <T>Future<T> submit(Runnable r, Comparator<Callable<T>> priority){
		return null;
	}
	
	public <T>Future<T> submit(Runnable r, Comparator<Callable<T>> priority, T value){
		return null;
	}
	
	public <T>Future<T> submit(Callable<T> c){
		return null;
	}
	
	public <T>Future<T> submit(Callable<T> c, Comparator<Callable<T>> priority){
		return null;
	}
	
	public void setNumOfThreads(int numOfThreads) {
		
	}
	
	public void pause() {
		
	}
	
	public void resume() {
		
	}
	
	public void shutDown() {
		
	}
	
	public void awaitTermination() {
		
	}
	
	enum PRIORITY{
		LOW,
		MEDIUM,
		HIGH
	}
}
