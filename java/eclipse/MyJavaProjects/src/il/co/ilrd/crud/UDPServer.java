package il.co.ilrd.crud;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class UDPServer extends Thread {
	private DatagramSocket datagramSocket;
	private boolean running = true;
	private byte[] buffer = new byte [4444];
	private CRUD<String, Long> database;
	
	public UDPServer(CRUD<String, Long> db) {
		try {
			database = db;
			datagramSocket = new DatagramSocket(4444);
		} catch (SocketException e) {
			e.printStackTrace();
		}
	}
	
	public void run() {
		while(running) {
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
			try {
				datagramSocket.receive(packet);
				System.out.println("received message");
			} catch (IOException e) {
				e.printStackTrace();
			}
			database.create(new String(packet.getData()));
		}
	}
}
