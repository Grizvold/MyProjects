package co.il.ilrd;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import com.sun.net.httpserver.HttpServer;

import org.json.JSONException;
import org.json.JSONObject;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class HttpServerIOT {
	private HttpServer server;
	private ExecutorService executor = Executors.newFixedThreadPool(10);
	private SingletonCommandFactory commandFactory = SingletonCommandFactory.getInstance();
	
	public HttpServerIOT(String addr, int port) throws IOException {
		server = HttpServer.create(new InetSocketAddress(addr, port), 0);
		server.createContext("/requests", new IOTHTTPHandler());
	}

	public void startServer() {
		server.start();
	}

	public void stopServer() {
		server.stop(0);
	}
	
	private class IOTHTTPHandler implements HttpHandler {	
		@Override
		public void handle(HttpExchange exchange) throws IOException {		
			if("GET".equals(exchange.getRequestMethod())) { 
				handleGetRequest(exchange);
				
			}else if("POST".equals(exchange.getRequestMethod())) { 
				try {
					handlePostRequest(exchange);
				} catch (JSONException e) {}
			}  
		}
		
		private String handleGetRequest(HttpExchange httpExchange) {
			return httpExchange.getRequestURI().toString().split("\\?")[1].split("=")[1];
		}
		
		private void handlePostRequest(HttpExchange httpExchange) throws JSONException {
			String str = new BufferedReader(new InputStreamReader(httpExchange.getRequestBody()))
					.lines().collect(Collectors.joining("\n"));
			
			JSONObject obj = new JSONObject(str);
			String type =  obj.getString("type");
			
			executor.submit(new HTTPTask(type, obj, httpExchange));
		}
	}
	
	private class HTTPTask implements Runnable {	
		private String command;
		private Object data;
		private HttpExchange httpExchange;
		private String response;
		private int statusCode;
		
		public HTTPTask(String command, Object data, HttpExchange httpExchange) {
			this.command = command;
			this.data = data;
			this.httpExchange = httpExchange;
		}
		
		@Override
		public void run() {
			if(commandFactory.create(command).execute(data)) {
				statusCode = 200;
			}
			else {
				statusCode = 500;
			}
			try {
				response = "status : " + statusCode;
				httpExchange.sendResponseHeaders(statusCode, response.getBytes().length);
				OutputStream os = httpExchange.getResponseBody();
				os.write(response.getBytes());
				os.flush();
				os.close();
			} catch (IOException e) {}
		}
	}		
}