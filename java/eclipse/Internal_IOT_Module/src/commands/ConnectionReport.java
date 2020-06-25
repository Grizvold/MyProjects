package commands;

public interface ConnectionReport<T> {
	public boolean send(T data);
}
