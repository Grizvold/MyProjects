package net.codejava.javaee;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Servlet implementation class HelloServlet
 */
@WebServlet("/helloServlet")
public class HelloServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public HelloServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String yourName = request.getParameter("yourName");
		PrintWriter writer = response.getWriter();
		writer.println("<h1>Hello " + yourName + "</h1>");
		writer.close();
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String nameString = req.getParameter("name");
		
		PrintWriter writer = resp.getWriter();
		writer.println("<h1>Hello " + nameString + "</h1>");
		writer.close();
	}
	
	protected void doPost1(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		StringBuffer sb = new StringBuffer();
	    BufferedReader bufferedReader = null;

	    try {
	        //InputStream inputStream = request.getInputStream();
	        //inputStream.available();
	        //if (inputStream != null) {
	        bufferedReader =  request.getReader(); //new BufferedReader(new InputStreamReader(inputStream));
	        char[] charBuffer = new char[128];
	        int bytesRead;
	        while ( (bytesRead = bufferedReader.read(charBuffer)) != -1 ) {
	            sb.append(charBuffer, 0, bytesRead);
	        }
	        //} else {
	        //        sb.append("");
	        //}

	    } catch (IOException ex) {
	        throw ex;
	    } finally {
	        if (bufferedReader != null) {
	            try {
	                bufferedReader.close();
	            } catch (IOException ex) {
	                throw ex;
	            }
	        }
	    }

	    String test = sb.toString();
	    @SuppressWarnings("unused")
		JSONObject obj;
	    try {
			obj = new JSONObject(test);
			PrintWriter writer = response.getWriter();
			writer.println("<h1> Hello " + test + "</h1>");
			writer.close();
		} catch (JSONException e) {
			e.printStackTrace();
		}
	   
	}
}
