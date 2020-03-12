package il.co.ilrd.crud;

import java.beans.PropertyChangeSupport;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.concurrent.TimeUnit;

public class LogMonitor{
	private String fileName = "";
	private boolean isRunning = true;
	private SeekableByteChannel readChannel = null;
	private PropertyChangeSupport dispatcher = null;
	private ByteBuffer byteBuffer = ByteBuffer.allocate(1024);
	private Thread monitoringThead = null;
	private Path pathToFile = null;
	private Path pathToDirectory = null;
	
	public LogMonitor(String fileName) throws IOException {
		pathToFile = Paths.get(fileName);
		pathToDirectory = pathToFile.getParent();
		this.fileName = pathToFile.getFileName().toString();
		try {
			monitoringThead = new Thread(new WatchedFileService(pathToDirectory));
			readChannel = Files.newByteChannel(pathToFile, StandardOpenOption.READ);
		} catch (IOException e) {
			e.printStackTrace();
		}
		dispatcher = new PropertyChangeSupport(monitoringThead);
		readChannel.position(readChannel.size());
	}
	
	public void startMonitoring() {
		monitoringThead.start();
	}
	
	public void stopMonitoring() {
		isRunning = false;
	}
	
	public void addListeners(UDPClient listener) {
		dispatcher.addPropertyChangeListener(listener);
	}
	
	class WatchedFileService implements Runnable{
		private WatchService watchService = null;
		private WatchKey watchKey = null;
		private Path path = null;
		
		public WatchedFileService(Path pathOfDirectory) throws IOException {
			path = pathOfDirectory;
			watchService = path.getFileSystem().newWatchService();
			path.register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
		}
		
		@Override
		public void run() {
			while(isRunning) {
				try {
					watchKey = watchService.poll(5, TimeUnit.SECONDS);
					if(watchKey != null) {
						for (WatchEvent<?> event: watchKey.pollEvents()) {
							if(((Path)event.context()).endsWith(fileName)) {
								while(readChannel.read(byteBuffer) > 0){
									byteBuffer.flip();
									dispatcher.firePropertyChange("", 
													null, 
													Charset.forName("UTF-8").decode(byteBuffer).toString());
									byteBuffer.clear();
								}
							}
						}
						watchKey.reset();
					}
				} catch (InterruptedException | IOException e) {
					e.printStackTrace();
				}
			}
		}
		
	}
}
