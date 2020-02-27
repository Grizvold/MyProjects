package il.co.ilrd.chat_room;

interface Server <G, U>{
	public void sendToClient(G groupName, U userName, String userMessage);
	public void addToGroup(G groupName, U userName, Conection clientConection);
	public void removeFromGroup(G groupName, U userName);
}
