package il.co.ilrd.chat_room;

import java.util.HashMap;
import java.util.LinkedList;

public class ChatServer implements Server<String, String>{
	private HashMap<String, LinkedList<Client>> mapOfUsers;
	
	public ChatServer() {
		mapOfUsers = new HashMap<>();
	}
	
	@Override
	public void sendToClient(String groupName, String userName, String userMessage) {
		for (Client client : mapOfUsers.get(groupName)) {
			if(!userName.equals(client.clientName)) {
				client.clientConection.sendMessage(userName + ": " + userMessage);
			}
		}
	}
	
	@Override
	public void addToGroup(String groupName, String userName, Conection clientConection) {
		if(!mapOfUsers.containsKey(groupName)) {
			mapOfUsers.put(groupName, new LinkedList<>());
		}
		mapOfUsers.get(groupName).add(new Client(clientConection, userName));
	}
	
	@Override
	public void removeFromGroup(String groupName, String userName) {
		LinkedList<Client> group = mapOfUsers.get(groupName);
		for (Client client : group) {
			if(userName.equals(client.clientName)) {
				group.remove(client);
				return;
			}
		}
	}
	
	private class Client {
		private Conection clientConection;
		private String clientName;
		
		private Client(Conection connection, String name) {
			clientConection = connection;
			clientName = name;
		}
	}

}
