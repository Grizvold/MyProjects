package il.co.ilrd.design_pattern.observer;

public class DispatcherTest {

	@SuppressWarnings("unused")
	public static void main(String[] args) throws InterruptedException {
		Client<String> pc1 = new Client<>();
		Client<String> pc2 = new Client<>();
		Client<String> pc3 = new Client<>();
		Client<String> pc4 = new Client<>();
		Producer<String> server = new Producer<>();
		String message = "first ping";
		
		server.registerClient(pc1);
		server.registerClient(pc2);
		server.registerClient(pc3);
		server.registerClient(pc4);
		
		Thread notificationThread = new Thread(new NotificationByTime<String>(server));
		
		notificationThread.start();
		
		Thread.sleep(3000);
		pc1.unregister();
		Thread.sleep(3000);
		pc2.unregister();
		Thread.sleep(3000);
		pc3.unregister();
		
		notificationThread.join();
	}	
}

class NotificationByTime<T> implements Runnable{

	private volatile int notification_number = 0; 
	private volatile boolean flag = true;
	private Producer<String> server;
	private String[] notificationMessage = {"1st ping", 
											"2nd ping", 
											"3rd ping", 
											"4th ping",
											"5th ping"};
	private long currentTime = System.currentTimeMillis();
	
	
	public NotificationByTime(Producer<String> server) {
		this.server = server;
	}
	
	@Override
	public void run(){
		while(flag) {
			
			server.notifyAll(notificationMessage[notification_number]);
			++notification_number;
			currentTime = System.currentTimeMillis();
			while(System.currentTimeMillis() - currentTime < 3000) {}
			
			if(notification_number > 4) {
				flag = false;
			}
			System.out.println("\n");
		}
	}
}