package il.co.ilrd.concurrency;

class ExtendedThread extends Thread
{   
    private volatile boolean flag = true;
     
    public void stopExtended()
    {
        flag = false;
    }
     
    @Override
    public void run()
    {
        while (flag)
        {
            System.out.println("ExtendedThread running....");
        }
         
        System.out.println("Stopped ExtendedThread ....");
    }
}

class RunnableThread implements Runnable
{
	/*private static volatile boolean flag = true;
	
	static void stopRunnable()
	{
		flag = false;
	}*/

	public void run() 
	{
		/*while(flag)*/
		while(!Thread.interrupted())
		{
			System.out.println("RunnableThread running....");
		}
		
		System.out.println("Stopped RunnableThread ....");
	}
}
 
public class Exercise1RunnableAndThread 
{   
    public static void main(String[] args) 
    {
    	ExtendedThread threadExtendedThread = new ExtendedThread();
    	Thread threadRunnableThread = new Thread(new RunnableThread());
         
    	threadExtendedThread.start();
    	threadRunnableThread.start();
    	
        try
        {
            Thread.sleep(5000);
        } 
        catch (InterruptedException e) 
        {
            e.printStackTrace();
        }
         
        threadExtendedThread.stopExtended();
        threadRunnableThread.interrupt();
    }   
}