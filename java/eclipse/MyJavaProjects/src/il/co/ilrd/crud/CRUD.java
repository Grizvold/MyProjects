package il.co.ilrd.crud;

import java.io.Serializable;

public interface CRUD <T extends Serializable, K extends Serializable> extends AutoCloseable{
	public K create(T target);
	public T read(K key);
	public void update(T target, K key);
	public void delete(K key);
}
