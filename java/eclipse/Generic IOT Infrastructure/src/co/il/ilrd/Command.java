package co.il.ilrd;

public interface Command<T> {
    boolean execute(T data);
}