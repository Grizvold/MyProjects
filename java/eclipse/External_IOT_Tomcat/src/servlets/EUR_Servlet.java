package servlets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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
 * Servlet implementation class EUR_Servlet
 */
@WebServlet("/end_users")
public class EUR_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public EUR_Servlet() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String requestAsJSONString = new BufferedReader(new InputStreamReader(request.getInputStream())).lines()
				.collect(Collectors.joining("\n"));
		JSONObject parsedObject = new JSONObject(requestAsJSONString);
		String company_id = "";
		String company_name = "";
		JSONObject nestedObject = null;
		String serial_number = "";
		int requested_product_id = 0;
		String first_name = "";
		String last_name = "";
		String email = "";
		String phone = "";
		String location = "";

		try {
			company_id = parsedObject.getString("company_id");
			company_name = parsedObject.getString("company_name");

			nestedObject = parsedObject.getJSONObject("data");
			requested_product_id = nestedObject.getInt("requested_product_id");
			first_name = nestedObject.getString("first_name");
			last_name = nestedObject.getString("last_name ");
			email = nestedObject.getString("email");
			phone = nestedObject.getString("phone");
			location = nestedObject.getString("location");
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		boolean status = dataBase_Establishment(company_name + company_id,
												requested_product_id,
												serial_number,
												first_name,
												last_name,
												email,
												phone,
												location);
		int status_Code = status ? 200 : 400;
		response.setStatus(status_Code);
		response.sendError(status_Code);
	}
	
	private static boolean dataBase_Establishment(String dbName,
												int requested_product_id,
		                                        String serial_number,        
		                                        String first_name,           
		                                        String last_name,            
		                                        String email,                
		                                        String phone,                
		                                        String location) {            
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
										first_name,
										last_name,
										email,
										phone,
										location,
										statement,
										dbConnection);
		
		try {
			statement.close();
			dbConnection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return isSuccess;
	}
	
	private static boolean dataBase_UpdateTable(String dbName, 
                                                 int requested_product_id,
		                                         String serial_number,
		                                         String first_name,
		                                         String last_name,    
		                                         String email,
		                                         String phone,    
		                                         String location,
		                                         Statement statement,
		                                         Connection connection) { 
		boolean isSuccess = false;
		int user_id = 0;
		String useDB = "USE " + dbName;
		String validationString = "SELECT COUNT(*) AS email FROM end_users_Table WHERE email=" + email + ") ";
		String creatingNewEndUser = "INSERT INTO end_users_Table (first_name, last_name, email, phone, location) "
			    		+ "VALUES('" + first_name + "', '" + last_name + "', '" + email+  "', '" + 
			    		phone + "', '" + location + "');";
		
		try {
			statement.executeUpdate(useDB);
			ResultSet isValid = statement.executeQuery(validationString);
			if(isValid.next()) {
				if(isValid.getInt("email") == 0) {
					PreparedStatement preparedStatement = connection.prepareStatement(creatingNewEndUser,
																						Statement.RETURN_GENERATED_KEYS);
					preparedStatement.execute();
					ResultSet resultSet = preparedStatement.getGeneratedKeys();
					if(resultSet.next()) {
						user_id = resultSet.getInt(1);
					}
				}
				else {
					String existingUserID = "SELECT user_id FROM end_users_Table WHERE email=" + email + ")";
					ResultSet resultSetID = statement.executeQuery(existingUserID);
					if(resultSetID.next()) {
						user_id = resultSetID.getInt("user_id");
					}
				}
			}
			
			String updateProductTableString = "INSERT INTO products_Table (product_type_id, serial_number, user_id) " + 
												"VALUES(" + requested_product_id + ",'" + serial_number +  
												"','" + user_id + "' );";
			statement.executeUpdate(updateProductTableString);
		} catch (SQLException e) {            	    	  									
			e.printStackTrace();
			return false;
		}
		
		isSuccess = true;
		return isSuccess;
	}

}
