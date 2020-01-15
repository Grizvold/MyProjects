package il.co.ilrd.concurrency;


public class Exercise2Block {
	public static int counter = 0;
	
	public static void main(String[] args) {
		Exercise2Block exercise2Block = new Exercise2Block();
		
		exercise2Block.startExecution();
		System.out.println("Counter Value: " + exercise2Block.getCounter());
	}
	
	public void startExecution() {
		Thread thread1 = new Thread(new RunnableThreadEx2Block());
		Thread thread2 = new Thread(new RunnableThreadEx2Block());
		
		long start = System.currentTimeMillis();
		thread1.start();
		thread2.start();
		
		try {
			thread1.join();
			thread2.join();
		} catch (Exception e) {
			// TODO: handle exception
		}
		long finish = System.currentTimeMillis();
		
		System.out.println("Execution time: " +  (finish - start));
	}
	
	public int getCounter() {
		return counter;
	}
	
}

class RunnableThreadEx2Block implements Runnable{
	private static Object monitorObject = new Object();
	
	@Override
	public void run() {
		for (int i = 0; i < 10000000; ++i) {
			synchronized (monitorObject) {
				++Exercise2Block.counter;
			}
		}
	}
}




