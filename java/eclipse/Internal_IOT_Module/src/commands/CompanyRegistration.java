package commands;

import org.json.JSONObject;

import co.il.ilrd.Command;

public class CompanyRegistration implements Command<Object>{
	HttpConnection connection;
	private final String urlString = "http://localhost:8080/DataTomcat/companies";
	
	public CompanyRegistration() {
		connection = new HttpConnection(urlString);
	}
	
	@Override
	public boolean execute(Object data) {
		return connection.send((JSONObject) data);
	}
	
}
