package commands;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.*;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.json.JSONObject;


//import org.apache.http.client.methods.HttpPost;


public class HttpConnection implements ConnectionReport<JSONObject>{
	private String urlString;
	
	public HttpConnection(String url) {
		urlString = url;
	}
	
	@Override
	public boolean send(JSONObject data) {
		boolean isSuccess = false;
		HttpPost postRequest = new HttpPost(urlString);
		
		try {
			postRequest.setEntity(new StringEntity(data.toString()));
			CloseableHttpClient httpClient = HttpClients.createDefault();
			HttpResponse httpResponse = httpClient.execute(postRequest);
			isSuccess = httpResponse.getStatusLine().getStatusCode() != 400;
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
			return isSuccess;
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return isSuccess;
		} catch (IOException e) {
			e.printStackTrace();
			return isSuccess;
		}
		
		return isSuccess;
	}

}
