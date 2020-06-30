package il.co.ilrd.chat_room;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.util.Iterator;
import java.util.Set;

public class ConnectionManager{
private ChatServer chatServer;
private Thread serverManager;
	
	public ConnectionManager(ChatServer chat) {
		chatServer = chat;
	}
	
	public void startManagement() {
		serverManager = new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					Selector selector = Selector.open();
					ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
					serverSocketChannel.bind(new InetSocketAddress("10.1.0.97", 5555));
					serverSocketChannel.configureBlocking(false);
					serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
					ByteBuffer buffer = ByteBuffer.allocate(1024);
					SocketChannel socketChannel = null;
					String message;
					
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
								message = Charset.forName("UTF-8").decode(buffer).toString();
								if(message.isEmpty()) {
									key.cancel();
								}
								else {									
									parseMessage(message, socketChannel);
								}
								
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
		});
		
		serverManager.start();
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
		int messageIndex = 0;
		String userName;
		String groupName;
		String message;
		
		if(userMessage.charAt(messageIndex) != STX || userMessage.charAt(userMessage.length() - 2) != ETX) {
			sendUnACK(socketChannel);
			return;
		}
		else {			
			sendACK(socketChannel, userMessage.charAt(++messageIndex));
		}
		
		typeOfMsg = userMessage.charAt(++messageIndex);//2
		lenghtOfGroupName = userMessage.charAt(++messageIndex);//3
		groupName = userMessage.substring(++messageIndex, messageIndex + lenghtOfGroupName);//4
		messageIndex += lenghtOfGroupName;  
		lenghtOfName = userMessage.charAt(messageIndex);
		userName = userMessage.substring(++messageIndex, messageIndex + lenghtOfName);
		switch (typeOfMsg) {
		case 'R':
			chatServer.addToGroup(groupName, userName, new SocketConnection(socketChannel));
			break;
			
		case 'M':
			messageIndex += lenghtOfName;
			lenghtOfMsg = userMessage.charAt(messageIndex);
			message = userMessage.substring(++messageIndex, messageIndex + lenghtOfMsg);
			chatServer.sendToClient(groupName, userName, message);
			break;
			
		case 'U':
			chatServer.removeFromGroup(groupName, userName);
			break;
			
		default:
			break;
		}
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
}
