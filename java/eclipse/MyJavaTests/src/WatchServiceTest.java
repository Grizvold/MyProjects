import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.concurrent.TimeUnit;

public class WatchServiceTest {
	public boolean isRunning = true; 
	public static String filePath1 = "/home/student/ruslan-gorbaty/files/watchTest1.txt";
	public static String filePath2 = "/home/student/ruslan-gorbaty/files/watchTest2.txt";
	public static String watchFilePath = "/home/student/ruslan-gorbaty/files/";
	
	public static String textString = "try try try";
	public static BufferedWriter writeBuffer1;
	public static BufferedWriter writeBuffer2;
	public static ByteBuffer byteBuffer = ByteBuffer.allocate(4096);
	public static SeekableByteChannel readChannel;
	public static SeekableByteChannel writeChannel;
	
	public static void main(String[] args) throws IOException {
		WatchServiceTest wst = new WatchServiceTest();
		WatchServiceTest.readChannel = Files.newByteChannel(Paths.get(filePath1), StandardOpenOption.READ);
		WatchServiceTest.writeChannel = Files.newByteChannel(Paths.get(filePath2), StandardOpenOption.WRITE);
		
		File watchTest1 = new File(filePath1);
		File watchTest2 = new File(filePath2);
		
		try {
			writeBuffer1 = new BufferedWriter(new FileWriter(watchTest1));
			writeBuffer2 = new BufferedWriter(new FileWriter(watchTest2));
			
			Thread writerThread = new Thread(wst.new WritterToFile(writeBuffer1, textString));
			Thread listenAndWriteThread = new Thread(wst.new WatchedFileService(watchFilePath));
			
			writerThread.start();
			listenAndWriteThread.start();

			writerThread.join();
			writeBuffer1.close();
			System.out.println("finished writting");
			
			wst.isRunning = false;
			listenAndWriteThread.join();
			
			writeBuffer2.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("end of test");
	}


	class WatchedFileService implements Runnable{
		private Path path;
		private WatchService watchService = null;
		private WatchKey watchKey = null; 
		
		public WatchedFileService(String pathToDirectory) throws IOException {
			path = Paths.get(pathToDirectory);
			watchService = path.getFileSystem().newWatchService();
			path.register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
		}
		
		@Override
		public void run() {
			while(isRunning) {
				try {
					watchKey = watchService.poll(10, TimeUnit.SECONDS);
					System.out.println(watchKey);
					if(watchKey != null){
						for (WatchEvent<?> event: watchKey.pollEvents()) {
							Path path = (Path)event.context();
							if(path.endsWith("watchTest1.txt")) {
								readChannel.read(byteBuffer);
								byteBuffer.flip();
								writeChannel.write(byteBuffer);
								byteBuffer.clear();
								System.out.println("Event kind: " + event.kind() + ". File affected: " + 
										event.context() + ".");
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
		
	class WritterToFile implements Runnable{
		private long currTime = 0l;
		private int count = 0;
		private BufferedWriter writterBuffer = null;
		private String output= "";
		
		public WritterToFile(BufferedWriter writterBuffer, String str) {
			this.writterBuffer = writterBuffer;
			output = str;
		}
		
		@Override
		public void run() {
			currTime = System.currentTimeMillis();
			while(count < 3) {
				if (System.currentTimeMillis() - currTime > 5000) {				
					try {
						writterBuffer.write("Writting number " + count+ " " + output + "\n");
						writterBuffer.flush();
						currTime = System.currentTimeMillis();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					System.out.println(count);
					++count;
				}
			}
		}
		
	}

}