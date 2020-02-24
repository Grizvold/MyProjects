package il.co.ilrd.chat_room;

public class Client {
	Conection clientConection;
	String clientName;
	
	public Client(Conection connection, String name) {
		clientConection = connection;
		clientName = name;
	}
}
