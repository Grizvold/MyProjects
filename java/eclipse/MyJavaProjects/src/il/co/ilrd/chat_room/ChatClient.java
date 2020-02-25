package il.co.ilrd.chat_room;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Arrays;
import java.util.Scanner;

public class ChatClient {
	private final static int connectionPort = 5555;
	
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		//InetAddress ipAddress = InetAddress.getByName("localhost");
		Socket socket = new Socket("10.1.0.119", connectionPort);
		
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
				
				while(true) {
					try {
						if(readBuffer.ready()) {
							readBuffer.read(buffer);
							System.out.println(String.valueOf(buffer));
							Arrays.fill(buffer, '\u0000');
						}
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		});
		
		sendMessageThread.start();
		readMessageThread.start();
	}
}
