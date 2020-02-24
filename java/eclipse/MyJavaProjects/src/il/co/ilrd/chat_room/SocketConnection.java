package il.co.ilrd.chat_room;

import java.io.IOException;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;

public class SocketConnection implements Conection{
	private SocketChannel socketChannel;
	
	public SocketConnection(SocketChannel channel) {
		socketChannel = channel;
	}
	
	@Override
	public void sendMessage(String message) {
		try {
			socketChannel.write(Charset.forName("UTF-8").encode(message));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
