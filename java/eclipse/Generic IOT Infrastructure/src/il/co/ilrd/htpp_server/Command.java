package il.co.ilrd.htpp_server;

public interface Command<T> {
    boolean execute(T data);
}