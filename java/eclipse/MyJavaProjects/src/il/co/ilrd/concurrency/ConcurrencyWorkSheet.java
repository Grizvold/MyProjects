package il.co.ilrd.concurrency;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class ConcurrencyWorkSheet {

	static void commands(ArrayList<String> commandList) throws Exception 
	{
		ProcessBuilder builder = new ProcessBuilder(commandList);
		Process localProcess = builder.start();
		String outputString = null;
		
		BufferedReader inputBufferedReader = 
				new BufferedReader(new InputStreamReader(localProcess.getInputStream()));
		BufferedReader erroReader = 
				new BufferedReader(new InputStreamReader(localProcess.getErrorStream()));
		
		System.out.println("Output: ");
		while ((outputString = inputBufferedReader.readLine()) != null) {
			System.out.println(outputString);
		}
		
		int exitValue = localProcess.waitFor();
		if(exitValue == 0) {
			System.out.println("No errors occured.");
			System.exit(0);
		}
		else {
			System.err.println("Error: " + erroReader.readLine());
		}
	}
	
	public static void main(String[] args) {
		ArrayList<String> commandList = new ArrayList<String>();
		
		commandList.add("ping");
		commandList.add("www,google.com");
		commandList.add("-i");
		commandList.add("1");
		
		try {
			ConcurrencyWorkSheet.commands(commandList);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
