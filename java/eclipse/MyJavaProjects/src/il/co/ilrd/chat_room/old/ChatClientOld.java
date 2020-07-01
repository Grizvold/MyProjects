package il.co.ilrd.chat_room.old;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
//import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;


public class ChatClientOld {
	final static int serverPort = 5555;
	
	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(System.in);
		//InetAddress ipAddress = InetAddress.getByName("localhost");
		Socket socket = new Socket("127.0.0.1", serverPort);
		
		DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
		DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
		
		Thread sendMessage = new Thread(new Runnable() {
			
			@Override
			public void run() {
				while(true) {
					String message = scan.nextLine();
					
					try {
						dataOutputStream.writeUTF(message);
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		});
		
		Thread readMessage = new Thread(new Runnable() {
			
			@Override
			public void run() {
				while(true) {
					try {
						String message = dataInputStream.readUTF();
						System.out.println(message);
					} catch (IOException e) {
						e.printStackTrace();
					}
					
				}
			}
		});
		
		sendMessage.start();
		readMessage.start();
		scan.close();
		socket.close();
	}
}
