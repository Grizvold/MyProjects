import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientTest {

	public static void main(String[] args) throws IOException, IOException {
		Socket clientSocket = new Socket("localhost", 5000);
		PrintWriter writer = new PrintWriter(clientSocket.getOutputStream());
		
		writer.println("I'm connected");
		writer.flush();
		
		
	}

}
