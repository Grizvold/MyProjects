package il.co.ilrd.crud;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.Charset;

public class UDPClient implements PropertyChangeListener{
	private DatagramSocket socket;
	private DatagramPacket packet;
	private InetAddress address;
	private int port;
	private byte[] buffer;
	
	public UDPClient(InetAddress userAddress, int userPort) {
		try {
			socket = new DatagramSocket();
			//change if needed
			//address = InetAddress.getByName("localhost");
			address = userAddress;
			port = userPort;
			buffer = new byte[1024];
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		buffer = ((String)evt.getNewValue()).getBytes(Charset.forName("UTF-8"));
		packet = new DatagramPacket(buffer, buffer.length, address, port);
		try {
			socket.send(packet);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
