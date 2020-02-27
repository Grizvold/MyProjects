package il.co.ilrd.chat_room;

public class ChatRoomTest {
	
	public static void main(String[] args) {
		ChatServer chatServer = new ChatServer();
		ConnectionManager manager = new ConnectionManager(chatServer);
		manager.startManagement();
	}
}
