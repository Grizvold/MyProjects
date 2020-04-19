package htpp_server;

public interface Command<T> {
    boolean execute(T data);
}