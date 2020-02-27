package il.co.ilrd.crud;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class UDPServer extends Thread {
	private DatagramSocket datagramSocket;
	private boolean running;
	private byte[] buffer = new byte [4444];
	private CRUDFile crudFile;
	
	public UDPServer() {
		try {
			crudFile = new CRUDFile("/home/student/ruslan-gorbaty/files/udp_file_update.txt");
			datagramSocket = new DatagramSocket(4444);
		} catch (SocketException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void run() {
		while(running) {
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
			try {
				datagramSocket.receive(packet);
			} catch (IOException e) {
				e.printStackTrace();
			}
			crudFile.create(new String(packet.getData()));
		}
	}
}
