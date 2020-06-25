package servlets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;
import java.util.stream.Collectors;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.JSONObject;

import com.mysql.cj.jdbc.Driver;

/**
 * Servlet implementation class IOT_UPDATE_Servlet
 */
@WebServlet("/iot_updates")
public class IOT_UPDATE_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public IOT_UPDATE_Servlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String requestAsJSONString = new BufferedReader(new InputStreamReader(request.getInputStream())).lines().collect(Collectors.joining("\n"));
		JSONObject parsedObject = new JSONObject(requestAsJSONString);
		JSONObject nestedObject = null;
		String company_id = "";
		String compane_name = "";
		String serial_number = "";
		String data_field1 = "";
		String data_field2 = "";
		String data_field3 = "";
		String user_time = "";
		int requested_product_id = 0;
		
		try {
			company_id = parsedObject.getString("company_id");
			compane_name = parsedObject.getString("compane_name");
			
			nestedObject = parsedObject.getJSONObject("data");
			requested_product_id = nestedObject.getInt("requested_product_id");
			user_time = nestedObject.getString("user_time");
			data_field1 = nestedObject.getString("data_field1");
			data_field2 = nestedObject.getString("data_field2");
			data_field3 = nestedObject.getString("data_field3");
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		boolean status = dataBase_Establishment(compane_name + company_id,
												serial_number,
												data_field1,
												data_field2,
												data_field3,
												user_time,
												requested_product_id);
		
		int status_Code = status ? 200 : 400;
		response.setStatus(status_Code);
		response.sendError(status_Code);
	}
	
	private static boolean dataBase_Establishment(String dbName, 
													String serial_number,
													String data_field1,
													String data_field2,
													String data_field3,
													String user_time,
													int requested_product_id) {
		boolean isSuccess = false;
		final String DB_URL = "jdbc:mysql://127.0.0.1/";
		Connection dbConnection = null;
		Statement statement = null;
		Driver connectionDriver = null;
		Properties properties = null;
		
		try {
			connectionDriver = new com.mysql.cj.jdbc.Driver();
			DriverManager.registerDriver(connectionDriver);
		} catch (SQLException e) {
			e.printStackTrace();
			return isSuccess;
		}
		
		properties = new Properties();
		properties.put("user", "root");
		properties.put("password", "");
		
		try {
			dbConnection = DriverManager.getConnection(DB_URL, properties);
			statement = dbConnection.createStatement();
		} catch (SQLException e) {
			e.printStackTrace();
			return isSuccess;
		}
		
		isSuccess = dataBase_UpdateTable(dbName, 
										requested_product_id,
										serial_number,
										data_field1,
										data_field2,
										data_field3,
										user_time,
										statement);
		
		try {
			statement.close();
			dbConnection.close();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		
		return isSuccess;
	}
	
	private static boolean dataBase_UpdateTable(String dbName,
												int requested_product_id,
												String serial_number,
												String data_field1,
												String data_field2,
												String data_field3,
												String user_time,
												Statement statement) {
		boolean isSuccess = false;
		String useDB = "USE " + dbName;
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		String dateFormatTime = dateFormat.format(date);
		String iOTupdateString = "INSERT INTO product_" + requested_product_id + 
				"_updates_table (serial_number, backend_time, user_time, data_field1, data_field2, data_field3) " + 
				"VALUES('" + serial_number + "', '" + dateFormatTime + "', '" + 
				user_time +  "', '" + data_field1 + "', '" + data_field2 + "', '" + data_field3 + "');";
		
		try {
			statement.executeUpdate(useDB);
			statement.executeUpdate(iOTupdateString);
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		
		isSuccess = true;
		return isSuccess;
	}
}
