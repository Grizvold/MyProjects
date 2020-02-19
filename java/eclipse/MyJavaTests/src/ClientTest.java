import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientTest {

	public static void main(String[] args) throws IOException, IOException, InterruptedException {
		Socket clientSocket = new Socket("localhost", 5000);
		
		PrintWriter writer = new PrintWriter(clientSocket.getOutputStream());
		writer.println("Is connection working?");
		writer.flush();
		
		InputStreamReader input = new InputStreamReader(clientSocket.getInputStream());
		BufferedReader reader = new BufferedReader(input);
		String inputString = reader.readLine();
		Thread.sleep(2000);
		System.out.println("server message: " + inputString);
		
		clientSocket.close();
	}

}
