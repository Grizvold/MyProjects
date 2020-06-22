import java.util.Scanner;

//import il.co.ilrd.chat_room.SocketConnection;

public class PraserOfChatMessageProtocol {

	public static void main(String[] args) {
		String groupName = "MyGroup";
		String name = "Ruslan";
		char groupLenght = (char) groupName.length();
		char nameLenght = (char) name.length();
		char STX = 0x02;
		char ETX = 0x03;
		
		
		parsingMessage(STX 
						+ "1R" 
						+ groupLenght 
						+ groupName 
						+ nameLenght 
						+ name 
						+ ETX);
		
		Scanner scanner = new Scanner(System.in);
		String message = scanner.nextLine();
		parsingMessage(STX 
							+ "1M" 
							+ groupLenght 
							+ groupName 
							+ nameLenght 
							+ name 
							+ (char)message.length() 
							+ message 
							+ ETX);
		
		scanner.close();
	}
	
	public static void parsingMessage(String userMessage) {
		
		System.out.println("starting");
		
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
			//sendUnACK(socketChannel);
			System.out.println("empty message");
		}
		
		if(userMessage.charAt(messageIndex) != STX || userMessage.charAt(userMessage.length() - 1) != ETX) {
			//sendUnACK(socketChannel);
			System.out.println("defective message");
		}
		
		System.out.println("starting parsing");
		
		messageID = userMessage.charAt(++messageIndex);//1
		
		System.out.println(messageID);
		
		typeOfMsg = userMessage.charAt(++messageIndex);//2
		
		System.out.println(typeOfMsg);
		
		lenghtOfGroupName = userMessage.charAt(++messageIndex);//3
		
		System.out.println(lenghtOfGroupName);
		
		groupName = userMessage.substring(++messageIndex, messageIndex + lenghtOfGroupName);//4
		
		System.out.println(groupName);
		
		messageIndex += lenghtOfGroupName;  
		lenghtOfName = userMessage.charAt(messageIndex);
		
		System.out.println(lenghtOfName);
		
		userName = userMessage.substring(++messageIndex, messageIndex + lenghtOfName);
		
		System.out.println(userName);
		
		
		
		switch (typeOfMsg) {
		case 'R':
			//chatServer.addToGroup(groupName, userName, new SocketConnection(socketChannel));
			System.out.println("registration message: " + groupName + " " + userName);
			break;
			
		case 'M':
			//chatServer.sendToClient(groupName, userName, userMessage);
			messageIndex += lenghtOfName;
			lenghtOfMsg = userMessage.charAt(messageIndex);
			
			System.out.println(lenghtOfMsg);
			
			message = userMessage.substring(++messageIndex, messageIndex + lenghtOfMsg);
			
			System.out.println(message);
			System.out.println("regular message: " + groupName + " " + userName + " " + message);
			break;
			
		case 'U':
			//chatServer.removeFromGroup(groupName, userName);
			System.out.println("unregister message: " + groupName + userMessage);
			break;
			
		default:
			break;
		}
	}
}
