package servlets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
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
 * Servlet implementation class CR_Servlet
 */
@WebServlet("/companies")
public class CR_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CR_Servlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String requestAsJSONString = new BufferedReader(new InputStreamReader(request.getInputStream())).lines().collect(Collectors.joining("\n"));
		String company_id = "";
		String company_name = "";
		JSONObject parsedObject = new JSONObject(requestAsJSONString);
		
		try { 
			company_id = parsedObject.getString("company_id");
			company_name = parsedObject.getString("company_name");
		} catch (Exception e) {
			// TODO: handle exception
		}
		
		boolean status = dataBase_Establishment(company_name + company_id);
		int status_Code = status ? 200 : 400;
		response.setStatus(status_Code);
		response.sendError(status_Code);
	}

	private static boolean dataBase_Establishment(String dbName) {
		final String DB_URL = "jdbc:mysql://127.0.0.1/";
		Connection dbConnection = null;
		Statement statement = null;
		Driver driver = null; 
		Properties properties = null;
		boolean isSuccess = false;
		
		try {
			driver = new com.mysql.cj.jdbc.Driver();
			DriverManager.registerDriver(driver);
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
		
		isSuccess = dataBase_Creation(dbName, statement);
		
		try {
			statement.close();
			dbConnection.close();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		
		return isSuccess;
	}
	
	private static boolean dataBase_Creation(String dbNameString, Statement statement) {
		boolean isSuccess = false;
		final String sqlCreateProductsTable = "CREATE TABLE products_Table (product_instance_id INT NOT NULL AUTO_INCREMENT,"
				+ " product_type_id INT,"
				+ " serial_number VARCHAR(20),"
				+ " user_id VARCHAR(20),"
				+ " PRIMARY KEY ( product_instance_id ));";
		
		final String sqlCreateEndUserTable = "CREATE TABLE end_users_Table (user_id INT NOT NULL AUTO_INCREMENT,"
				+ " first_name VARCHAR(20),"
				+ " last_name VARCHAR(20),"
				+ " email VARCHAR(30),"
				+ " phone VARCHAR(30),"
				+ " location VARCHAR(30),"
				+ " PRIMARY KEY ( user_id ));";
		
		String createDB = "CREATE DATABASE " + dbNameString;
		String useDB = "USE " + dbNameString;
		
		
		try {
			statement.executeUpdate(createDB);
			statement.executeUpdate(useDB);
			statement.executeUpdate(sqlCreateProductsTable);
			statement.executeUpdate(sqlCreateEndUserTable);
		} catch (SQLException e) {
			e.printStackTrace();
			return isSuccess;
		}
		
		isSuccess = true;
		return isSuccess;
	}
}
