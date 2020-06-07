import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.SortedMap;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import com.jramoyo.io.IndexedFileReader;

public class ReadCsvFile {
	static String pathToFile = "";
	
	public static void main(String[] args) throws IOException {
		pathToFile = args[0];
		try {
			System.out.println(findDomainFromIp(733846));
			System.out.println(findIpFromDomain("removepcvirusthreats.com"));
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		
	}
	
	
	static String findDomainFromIp(Integer ip) throws InterruptedException, ExecutionException {
		ExecutorService executorService = Executors.newFixedThreadPool(8);
		List<Future<String>> resList = new ArrayList<>();
		
		for (int i = 0, j = 1; i < 8; i++, j += 125000) {			
			resList.add(executorService.submit(new WorkingThreadIp(j, j + 125000, ip)));
		}
		
		executorService.shutdown();
		
		for (int i = 0; i < resList.size(); i++) {
			if(resList.get(i).get() != null) {
				return resList.get(i).get();
			}
		}
		return null;
	}
	
	static String findIpFromDomain(String domain) throws InterruptedException, ExecutionException {
		ExecutorService executorService = Executors.newFixedThreadPool(8);
		List<Future<String>> resList = new ArrayList<>();
		
		for (int i = 0, j = 1; i < 8; i++, j += 125000) {			
			resList.add(executorService.submit(new WorkingThreadDomain(j, j + 125000, domain)));
		}
		
		executorService.shutdown();
		
		for (int i = 0; i < resList.size(); i++) {
			if(resList.get(i).get() != null) {
				return resList.get(i).get();
			}
		}
		return null;
	}	
	
	
	static String findDomain(Integer ip, int from, int to) throws IOException {
		
		File file = new File(ReadCsvFile.pathToFile);
		IndexedFileReader reader = new IndexedFileReader(file);

		SortedMap<Integer, String> lines/* = reader.head(5)*/;

		lines = reader.readLines(from, to);
		reader.close();
		for (int i = from; i < to; i++) {
			if(lines.get(i).split(",")[0].equals(ip.toString())){
				return lines.get(i).split(",")[1];
			}
		}
		
		return null;
	}
	
	static String findDomain(String domain, int from, int to) throws IOException {	
		
		File file = new File(ReadCsvFile.pathToFile);
		IndexedFileReader reader = new IndexedFileReader(file);

		SortedMap<Integer, String> lines;

		lines = reader.readLines(from, to);
		reader.close();
		for (int i = from; i < to; i++) {
			if(lines.get(i).split(",")[1].equals(domain)){
				return lines.get(i).split(",")[0];
			}
		}
		return null;
	}

}


class WorkingThreadIp implements Callable<String>{
	int from;
	int to;
	Integer ip;
	
	public WorkingThreadIp(int from, int to, Integer ip) {
		this.ip = ip;
		this.from = from;
		this.to = to;
	}	
	
	@Override
	public String call() throws Exception {
		return ReadCsvFile.findDomain(ip, from, to);
	}
}


class WorkingThreadDomain implements Callable<String>{
	int from;
	int to;
	String domain;
	
	public WorkingThreadDomain(int from, int to, String domain) {
		this.domain = domain;
		this.from = from;
		this.to = to;
	}	
	
	@Override
	public String call() throws Exception {
		return ReadCsvFile.findDomain(domain, from, to);
	}
	
}