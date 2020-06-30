package il.co.ilrd.chat_room;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ChatClient {
	private final static int connectionPort = 5555;
	
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		//InetAddress ipAddress = InetAddress.getByName("localhost");
		Socket socket = new Socket("10.1.0.97", connectionPort);//10.1.0.119
		
		PrintWriter printWriter = new PrintWriter(socket.getOutputStream(), true);
		InputStreamReader inputStream = new InputStreamReader(socket.getInputStream());
		BufferedReader readBuffer = new BufferedReader(inputStream);
		
		Thread sendMessageThread = new Thread(new Runnable() {
			String groupName = "MyGroup";
			String name = "Ruslan";
			char groupLenght = (char) groupName.length();
			char nameLenght = (char) name.length();
			char STX = 0x02;
			char ETX = 0x03;
			
			@Override
			public void run() {
				
				printWriter.println(STX 
									+ "1R" 
									+ groupLenght 
									+ groupName 
									+ nameLenght 
									+ name 
									+ ETX);

				while(true) {
					String message = scanner.nextLine();
					printWriter.println(STX 
							+ "1M" 
							+ groupLenght 
							+ groupName 
							+ nameLenght 
							+ name 
							+ (char)message.length() 
							+ message 
							+ ETX);
				}
			}
		});
		
		Thread readMessageThread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				char[] buffer = new char[1024];
				String message;
				
				while(true) {
					try {
						if(readBuffer.ready()) {
							readBuffer.read(buffer);
							message = new String(buffer); 
							System.out.println(message);
//							if(message.charAt(2) != 0x06 && 
//									message.charAt(2) != 0x015) {
//								System.out.println(message);
//							}
							buffer = new char [1024];
						}
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		});
		
		sendMessageThread.start();
		readMessageThread.start();
		
		
		try {
			sendMessageThread.join();
			readMessageThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		scanner.close();
		socket.close();
	}
}
