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
	private ByteBuffer byteBuffer = ByteBuffer.allocate(4096);
	private Thread monitoringThead = null;
	
	public LogMonitor(String pathToDirectory, String fileName) throws IOException {
		try {
			monitoringThead = new Thread(new WatchedFileService(pathToDirectory));
			readChannel = Files.newByteChannel(Paths.get(pathToDirectory + fileName), 
												StandardOpenOption.READ);
		} catch (IOException e) {
			e.printStackTrace();
		}
		dispatcher = new PropertyChangeSupport(monitoringThead);
		this.fileName = fileName;
		readChannel.position(readChannel.size());
	}
	
	public void startMonitoring() {
		monitoringThead.start();
	}
	
	public void stopMonitoring() {
		isRunning = false;
	}
	
	public void addListeners(Listener listener) {
		dispatcher.addPropertyChangeListener(listener);
	}
	
	class WatchedFileService implements Runnable{
		private WatchService watchService = null;
		private WatchKey watchKey = null;
		private Path path = null;
		
		public WatchedFileService(String pathToDirectory) throws IOException {
			path = Paths.get(pathToDirectory);
			watchService = path.getFileSystem().newWatchService();
			path.register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
		}
		
		@Override
		public void run() {
			while(isRunning) {
				try {
					watchKey = watchService.poll(10, TimeUnit.MINUTES);
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
