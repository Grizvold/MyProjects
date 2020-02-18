package il.co.ilrd.crud;

import java.io.IOException;
import java.nio.channels.SeekableByteChannel;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class CRUDFile implements CRUD<String, Long>{
	private Path pathToFile;
	public SeekableByteChannel writeChannel;
	private Long position = 0l; 
	
	public CRUDFile(String path) throws IOException {
		pathToFile = Paths.get(path);
		writeChannel = Files.newByteChannel(pathToFile, StandardOpenOption.WRITE);
	}
	
	@Override
	public Long create(String dataToWrite) {
		try {
			position = writeChannel.position();
			writeChannel.write(Charset.forName("UTF-8").encode(dataToWrite));
		} catch (IOException e) {
			e.printStackTrace();
		}
		return position;
	}

	@Override
	public void close() throws Exception {
		writeChannel.close();
	}


	@Override
	public String read(Long key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void update(String target, Long key) {
		// TODO Auto-generated method stub
	}

	@Override
	public void delete(Long key) {
		// TODO Auto-generated method stub
	}

}
