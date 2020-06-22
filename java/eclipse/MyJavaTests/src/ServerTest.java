import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerTest {
	
	private static String messageString = "";
	
	public static void main(String[] args) throws IOException, InterruptedException {
		boolean flag = true;
		int portNumber = 5000;
		ServerSocket serverSocket = new ServerSocket(portNumber);
		Socket connectionSocket = serverSocket.accept();
		
		System.out.println("Client connected succesfully");
		
		PrintWriter writer = new PrintWriter(connectionSocket.getOutputStream(), true);
		InputStreamReader inputStream = new InputStreamReader(connectionSocket.getInputStream());
		BufferedReader readerBuffer = new BufferedReader(inputStream);

		new Thread(new ReadBufferThread()).start();
		
		while(flag) {
			if(readerBuffer.ready()) {
				System.out.println("Client message: " + readerBuffer.readLine());
			}
			
			if(!messageString.isEmpty()) {
				writer.println(messageString);
				messageString = "";
			}
		}
		
		serverSocket.close();
	}
	
	
	public static class ReadBufferThread implements Runnable{

		BufferedReader readingBuffer = new BufferedReader(new InputStreamReader(System.in));
		
		@Override
		public void run() {
			while(true) {
					try {
						messageString = readingBuffer.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
}

