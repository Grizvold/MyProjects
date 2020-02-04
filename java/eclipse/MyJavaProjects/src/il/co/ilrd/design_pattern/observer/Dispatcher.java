package il.co.ilrd.design_pattern.observer;

import java.util.List;
import java.util.function.Consumer;

public class Dispatcher<T>{
	private List<CallBack<T>> list;
	
	public void updateAll(T t) {
	}
	
	public void stop() {
	}
	
	public void register(CallBack<T> callback) {
		
	}
	
	public void unregister(CallBack<T> callback) {
		
	}
}

class CallBack<T>{
	private Dispatcher<T> dispatcher;
	Consumer<T> notify;
	Consumer<T> notifyDeath;
	
	public CallBack(Consumer<T> notify, Consumer<T> notifydeath) {
		this.notify = notify;
		this.notifyDeath = notifydeath;
		dispatcher.register(this);
	}
	
	public void notify(Object args) {
		
	}
	
	public void notifyDeath() {
		
	}
	
	public void unregister() {
		
	}
}