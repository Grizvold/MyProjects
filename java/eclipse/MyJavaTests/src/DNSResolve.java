import java.io.File;
import java.io.IOException;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.SortedMap;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import com.jramoyo.io.IndexedFileReader;

public class DNSResolve {
	private final static int number_of_threads = 4;
	private final static int jump_range_on_csv = 250;
	private static String pathToFile = "";
	private static Map<String, String> dnsMap = new HashMap<>();
	private static final int timeUnitAmount = 10;
	private static final TimeUnit timeUnitType = TimeUnit.MINUTES;
	
//	private static String pathToDNSResolveTable = "/home/student/Downloads/dns_resolve_table.csv";
	
	public static void main(String[] args) throws InterruptedException, ExecutionException{
		pathToFile = args[0];
		Integer option = Integer.parseInt(args[1]);
		
		//ip to host_name
		if(option.intValue() == 1) {
			findDomainFromIp(null);
		}
		//host_name to ip
		else if (option.intValue() == 2) {
			findIpFromDomain(null);
		}
	}
	
	private static void printDNSMap() {
		int i = 0; 
		for (Map.Entry<String, String> entry : dnsMap.entrySet()) {
			++i;
		    System.out.println(i + " " + entry.getKey() + " : " + entry.getValue().toString());
		}
	}
	
	private static void findDomainFromIp(Integer ip) throws InterruptedException, ExecutionException {
		ExecutorService executorService = Executors.newFixedThreadPool(number_of_threads);
		List<Future<String>> futureTaskList = new ArrayList<>();
		
		for (int i = 0, j = 1; i < number_of_threads; i++, j += jump_range_on_csv) {			
			futureTaskList.add(executorService.submit(new Worker_IPtoHostname(j, j + jump_range_on_csv, ip)));
		}
		
		executorService.shutdown();
		executorService.awaitTermination(timeUnitAmount, timeUnitType);
		printDNSMap();
		//getting return value from tasks
//		for (int i = 0; i < resList.size(); i++) {
//			if(resList.get(i).get() != null) {
//				return resList.get(i).get();
//			}
//		}
//		return null;
	}
	
	private static void findIpFromDomain(String domain) throws InterruptedException, ExecutionException {
		ExecutorService executorService = Executors.newFixedThreadPool(number_of_threads);
		List<Future<String>> futureTaskList = new ArrayList<>();
		
		for (int i = 0, j = 1; i < number_of_threads; i++, j += jump_range_on_csv) {			
			futureTaskList.add(executorService.submit(new Worker_HostnametoIP(j, j + jump_range_on_csv, domain)));
		}
		
		executorService.shutdown();
		executorService.awaitTermination(timeUnitAmount, timeUnitType);
		printDNSMap();
		//getting return value from tasks
//		for (int i = 0; i < resList.size(); i++) {
//			if(resList.get(i).get() != null) {
//				return resList.get(i).get();
//			}
//		}
//		return null;
	}	
	
	
	public static String findDomain(Integer ip, int from, int to) throws IOException {
		
		File file = new File(DNSResolve.pathToFile);
		IndexedFileReader reader = new IndexedFileReader(file);

		SortedMap<Integer, String> lines;

		lines = reader.readLines(from, to);
		reader.close();
		for (int i = from; i < to; i++) {
			String ipAddress = lines.get(i).split(",")[0];
			
			try {
				InetAddress address = InetAddress.getByName(ipAddress);
				String hostName = address.getHostName();
				dnsMap.put(hostName, ipAddress);
			} catch (Exception e) {
				dnsMap.put("not_found", ipAddress);
			}
		}
		return null;
	}
	
	public static String findDomain(String domain, int from, int to) throws IOException {	
		
		File file = new File(DNSResolve.pathToFile);
		IndexedFileReader reader = new IndexedFileReader(file);

		SortedMap<Integer, String> lines;

		lines = reader.readLines(from, to);
		reader.close();

//		FileWriter outputFile = new FileWriter(new File(pathToDNSResolveTable));
		for (int i = from; i < to; i++) {
			String hostName = lines.get(i).split(",")[1];

			try {
				InetAddress address = InetAddress.getByName(hostName);
				String ipString = address.getHostAddress();
				dnsMap.put(hostName, ipString);
				
				/* write back to file*/
//				outputFile.append(ipString);
//				outputFile.append(",");
//				outputFile.append(hostName);
//				outputFile.append("\n");
//				outputFile.flush();
			} catch (Exception e) {
				//in case bad hostname was received
				dnsMap.put(hostName, "0.0.0.0");
			}
		}
//		outputFile.close();
		return null;
	}
}


class Worker_IPtoHostname implements Callable<String>{
	private int from;
	private int to;
	private Integer ip;
	
	public Worker_IPtoHostname(int from, int to, Integer ip) {
		this.ip = ip;
		this.from = from;
		this.to = to;
	}	
	
	@Override
	public String call() throws Exception {
		return DNSResolve.findDomain(ip, from, to);
	}
}

class Worker_HostnametoIP implements Callable<String>{
	private int from;
	private int to;
	private String domain;
	
	public Worker_HostnametoIP(int from, int to, String domain) {
		this.domain = domain;
		this.from = from;
		this.to = to;
	}	
	
	@Override
	public String call() throws Exception {
		return DNSResolve.findDomain(domain, from, to);
	}
}