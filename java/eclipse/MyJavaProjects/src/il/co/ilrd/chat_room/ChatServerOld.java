package il.co.ilrd.chat_room;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.StringTokenizer;
import java.util.Vector;

public class ChatServerOld {
	//static HashMap<String, List<ClientHandler>> mapOfUsers = new HashMap<>();
	static Vector<ClientHandler> mapOfUsers = new Vector<>();
	static int clientCounter = 0;
	
	public static void main(String[] args) throws IOException {
		ServerSocket serverSocket = new ServerSocket(5000);
		Socket socket;
		boolean flag = true;
		
		while(flag) {
			socket = serverSocket.accept();
			System.out.println("New client request received: " + socket);
			
			DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
			DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
			
			System.out.println("Creating registry of new client");
			ClientHandler client = new ClientHandler(socket,
													dataInputStream,
													dataOutputStream,
													"client" + clientCounter);
			
			Thread registrationThread = new Thread(client);
			System.out.println("Adding new client to active client list");
			mapOfUsers.add(client);
			registrationThread.start();
			++clientCounter;
		}
		
		serverSocket.close();
	}

}

class ClientHandler implements Runnable{
	private String nameOfClient = null;
	private DataInputStream dataInput;
	private DataOutputStream dataOutput;
	private Socket clientSocket;
	private boolean isLogedIn;
	
	public ClientHandler(Socket socket, 
						DataInputStream dataInputStream, 
						DataOutputStream dataOutputStream,
						String name) {
		clientSocket = socket;
		dataInput = dataInputStream;
		dataOutput = dataOutputStream;
		nameOfClient = name;
		isLogedIn = true;
	}

	@Override
	public void run() {
		String received;
		while(true) {
			try {
				received = dataInput.readUTF();
				
				System.out.println(received);
				if(received.equals("logout")) {
					this.isLogedIn = false;
					this.clientSocket.close();
					break;
				}
				
				StringTokenizer stringToken = new StringTokenizer(received, "#");
				String msgToSend = stringToken.nextToken();
				String recipient = stringToken.nextToken();
				
				for (ClientHandler c : ChatServerOld.mapOfUsers) {
					//if client is found in list of users send message
					if(c.nameOfClient.equals(recipient) && c.isLogedIn == true) {
						c.dataOutput.writeUTF(this.nameOfClient + " : " + msgToSend);
						break;
					}
				}
				
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			try {
				this.dataInput.close();
				this.dataOutput.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
}