package il.co.ilrd.chat_room;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;
import java.util.PrimitiveIterator.OfDouble;

public class ChatServer {
	HashMap<String, LinkedList<Client>> mapOfUsers;
	
	
	public static void main(String[] args) {
		
	}
	
	public ChatServer() {
		mapOfUsers = new HashMap<>();
	}
	
	private void sendToClient(String groupName, String userName, String userMessage) {
		for (Client client : mapOfUsers.get(groupName)) {
			if(!userName.equals(client.clientName)) {
				client.clientConection.sendMessage(userMessage);
			}
		}
	}
	
	private void addToGroup(String groupName, String userName, Conection clientConection) {
		if(!mapOfUsers.containsKey(groupName)) {
			mapOfUsers.put(groupName, new LinkedList<>());
		}
		
		mapOfUsers.get(groupName).add(new Client(clientConection, userName));
	}
	
	private void removeFromGroup(String groupName, String userName) {
		mapOfUsers.remove(groupName, userName);
	}
}

class ChatSelector implements Runnable{
	private ChatServer chatServer;
	
	public ChatSelector(ChatServer chat) {
		chatServer = chat;
	}
	
	private void parseMessage(String userMessage, SocketChannel socketChannel) {
		//TODO protocol of message: STX.ID(of message).T(type).len.Group_Name.len.name.len.msg.ETX
		//TODO STX:0x02 ETX:0x03
		char STX = 0x02;
		char ETX = 0x03;
		char typeOfMsg;
		int lenghtOfGroupName;
		int lenghtOfName;
		int lenghtOfMsg;
		int messageID;
		int messageIndex = 0;
		String userName;
		String groupName;
		String message;
		
		//if the packet is empty
		if(userMessage.equals("")) {
			sendUnACK(socketChannel);
		}
		
		if(userMessage.charAt(messageIndex) != STX || userMessage.charAt(userMessage.length() - 1) != ETX) {
			sendUnACK(socketChannel);
		}
		
		messageID = userMessage.charAt(++messageIndex);//1
		typeOfMsg = userMessage.charAt(++messageIndex);//2
		lenghtOfGroupName = userMessage.charAt(++messageIndex);//3
		groupName = userMessage.substring(++messageIndex, messageIndex + lenghtOfGroupName);//4
		messageIndex += lenghtOfGroupName + 1;  
		lenghtOfName = userMessage.charAt(messageIndex);
		userName = userMessage.substring(++messageIndex, messageIndex + lenghtOfName);
		messageIndex += lenghtOfName + 1;
		lenghtOfMsg = userMessage.charAt(messageIndex);
		message = userMessage.substring(++messageIndex, messageIndex + lenghtOfMsg);
	}
	
	private void registerToChat(Selector selector, ServerSocketChannel serverSocketChannel) throws IOException {
		SocketChannel socketClient = serverSocketChannel.accept();
		socketClient.configureBlocking(false);
		socketClient.register(selector, SelectionKey.OP_READ);
		sendACK(socketClient, '0');
	}
	
	private void sendACK(SocketChannel socketChannel, char id) {
		try {
			socketChannel.write(Charset.forName("UTF-8").encode(String.format("%c%c%c%c", 
																0x02, id, 0x06, 0x03)));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void sendUnACK(SocketChannel socketChannel) {
		//TODO protocol of registration: STX.ID.ACK/UNACK (0x06. 0x15).ETX
		try {
			socketChannel.write(Charset.forName("UTF-8").encode(String.format("%c%c%c%c", 
																	0x02, 0x00, 0x015, 0x03)));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void run() {
		try {
			Selector selector = Selector.open();
			ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
			serverSocketChannel.bind(new InetSocketAddress("localhost", 5000));
			serverSocketChannel.configureBlocking(false);
			serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
			ByteBuffer buffer = ByteBuffer.allocate(1024);
			SocketChannel socketChannel = null;
			
			while(true) {
				selector.select();
				Set<SelectionKey> selectedKeys = selector.selectedKeys();
				Iterator<SelectionKey> iter = selectedKeys.iterator();
				while(iter.hasNext()) {
					SelectionKey key = iter.next();
					
					if(key.isAcceptable()) {
						registerToChat(selector, serverSocketChannel);
					}
					
					if(key.isReadable()) {
						socketChannel = (SocketChannel) key.channel();
						socketChannel.read(buffer);
						buffer.flip();
						parseMessage(Charset.forName("UTF-8").decode(buffer).toString(), 
																				socketChannel);
						buffer.clear();
						socketChannel = null;
					}
					
					iter.remove();
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
