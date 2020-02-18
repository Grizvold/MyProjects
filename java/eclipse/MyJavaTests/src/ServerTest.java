import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerTest {

	public static void main(String[] args) throws IOException {
		ServerSocket serverSocket = new ServerSocket(5000);
		Socket connectionSocket = serverSocket.accept();
		
		System.out.println("Client connected succesfully");
		InputStreamReader input = new InputStreamReader(connectionSocket.getInputStream());
		BufferedReader reader = new BufferedReader(input);
		String inputString = reader.readLine();
		System.out.println("Message from client: " + inputString);
	}

}
