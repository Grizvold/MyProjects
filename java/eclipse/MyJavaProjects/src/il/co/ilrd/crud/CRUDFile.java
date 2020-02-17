package il.co.ilrd.crud;

import java.io.IOException;
import java.nio.channels.SeekableByteChannel;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class CRUDFile implements CRUD<String, Long>{
	private Path path;
	public SeekableByteChannel writeChannel;
	
	public CRUDFile(String path) throws IOException {
		this.path = Paths.get(path);
		writeChannel = Files.newByteChannel(this.path, StandardOpenOption.WRITE);
	}
	
	@Override
	public Long create(String dataToWrite) {
		Long bufferSize = 0l;
		try {
			bufferSize = new Long(writeChannel.write(Charset.forName("UTF-8").encode(dataToWrite)));
		} catch (IOException e) {
			e.printStackTrace();
		}
		return bufferSize;
	}

	@Override
	public void close() throws Exception {
		// TODO Auto-generated method stub
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
