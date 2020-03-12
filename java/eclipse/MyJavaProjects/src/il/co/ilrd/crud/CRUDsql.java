package il.co.ilrd.crud;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;


public class CRUDsql implements CRUD<String, Long> {
	String dataBaseURL = "jdbc:mysql://localhost:3306/CRUDdb";
	String user = "root";
	String password = "";
	Connection dbConnection = null;
	PreparedStatement statement = null;
	
	public CRUDsql() {
		try {
			dbConnection = DriverManager.getConnection(dataBaseURL, user, password);
			dbConnection.setAutoCommit(false);
			statement = dbConnection.prepareStatement("INSERT INTO Syslogupdate (updateinfo) VALUES (?)");
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void close() throws Exception {
		statement.close();
		dbConnection.close();		
	}

	@Override
	public Long create(String element) {
		System.out.println("inside create method\n" +  element);
		int idx = 0;
		
		try {
			statement.setString(1, element);
			idx = statement.executeUpdate();
			dbConnection.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return (long)idx;
	}
	

	@Override
	public String read(Long key) {
		throw new NotImplementedException();
	}


	@Override
	public void delete(Long key) {
		throw new NotImplementedException();
	}

	@Override
	public void update(String target, Long key) {
		// TODO Auto-generated method stub
		
	}

}

