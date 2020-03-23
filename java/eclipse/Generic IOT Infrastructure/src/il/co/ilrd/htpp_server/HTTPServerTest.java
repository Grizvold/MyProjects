package il.co.ilrd.htpp_server;

import java.io.FileWriter;
import java.io.IOException;
import org.json.JSONException;
import org.json.JSONObject;

public class HTTPServerTest {
	public static void main(String[] args) throws IOException {
		SingletonCommandFactory factory = SingletonCommandFactory.getInstance();
		
		Command<Object> wl = (Object data)->{
		try {
			FileWriter myWriter = new FileWriter("/home/ruslan/ruslan-gorbaty/logfile.txt", true);
			try {
				myWriter.write(((JSONObject)data).getString("data"));
			} catch (JSONException e) {
				myWriter.close();
				return false;
			}
			myWriter.close();
		} catch (IOException e) {
		return false;
		}
		return true;};
		
		factory.add("wl", wl);
		
		HttpServerIOT server = new HttpServerIOT("localhost", 1111);
		server.startServer();
	}
}
