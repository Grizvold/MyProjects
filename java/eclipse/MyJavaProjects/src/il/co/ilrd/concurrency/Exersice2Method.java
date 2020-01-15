package il.co.ilrd.concurrency;

public class Exersice2Method {

	public static int counter = 0;
	
	public static void main(String[] args) {
		Exersice2Method exercise2 = new Exersice2Method();
		
		exercise2.startExecution();
		System.out.println("Counter Value: " + exercise2.getCounter());
	}

	public void startExecution() {
		Thread thread1 = new Thread(new RunnableThreadEx2Method());
		Thread thread2 = new Thread(new RunnableThreadEx2Method());
		
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

class RunnableThreadEx2Method implements Runnable{
	@Override
	public synchronized void run() {
		for (int i = 0; i < 10000000; ++i) {
			++Exersice2Method.counter;
		}
	}
}
