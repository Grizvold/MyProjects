package il.co.ilrd.crud;

import java.net.InetAddress;
import java.util.Scanner;

public class CRUDTest {
	public static void main(String[] args) throws Exception {		
		LogMonitor monitor = new LogMonitor("/var/log/syslog");
		InetAddress clientAddress = InetAddress.getByName("10.1.0.134");
		UDPClient client = new UDPClient(clientAddress, 4444);
		
		monitor.addListeners(client);
		monitor.startMonitoring();
		
		Runtime.getRuntime().exec("/usr/bin/x-terminal-emulator --disable-factory -e cat README.txt");
		
		String inputString = "";
		Scanner scanner = new Scanner(System.in);
		
		while(!inputString.equals("exit")) {
			inputString = scanner.nextLine();
			System.out.println(inputString);
		}
		
		scanner.close();
		monitor.stopMonitoring();
		Runtime.getRuntime().exec("/usr/bin/x-terminal-emulator --disable-factory -e cat README.txt");
		
		System.out.println("Done");
	}
}
