import java.net.InetAddress;
import java.net.UnknownHostException;

public class DNSResolveTest {

	public static void main(String[] args) throws UnknownHostException {
		InetAddress address = InetAddress.getByName("www.example.com"); 
		System.out.println(address.getHostAddress()); 
		
		InetAddress address2 = InetAddress.getByName("172.217.169.46");
		System.out.println(address2.getHostName());
		
		InetAddress addr = InetAddress.getByName("23.229.203.68");
		System.out.println("Host name is: " + addr.getHostName());
		System.out.println("Ip address is: " + addr.getHostAddress());
	}
}

