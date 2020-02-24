package il.co.ilrd.chat_room;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class ChatClient {
	private final static int connectionPort = 5000;
	
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		InetAddress ipAddress = InetAddress.getByName("localhost");
		Socket socket = new Socket(ipAddress, connectionPort);

		DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
		DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
		
		Thread sendMessageThread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				while(true) {
					String message = scanner.nextLine();
					try {
						dataOutputStream.writeUTF(message);
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		});
		
		Thread readMessageThread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					String message = dataInputStream.readUTF();
					System.out.println(message);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});
		
		sendMessageThread.start();
		readMessageThread.start();
	}
}
