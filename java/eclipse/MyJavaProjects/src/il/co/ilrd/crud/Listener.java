package il.co.ilrd.crud;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;

public class Listener implements PropertyChangeListener{
	private CRUDFile crudFile = null;
	
	public Listener(String updatedFilePath) {
		try {
			crudFile = new CRUDFile(updatedFilePath);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		this.crudFile.create((String) evt.getNewValue());
	}
}
