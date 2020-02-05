package il.co.ilrd.design_pattern.observer;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Consumer;

public class Dispatcher<T>{
	private List<CallBack<T>> list = new LinkedList<>();
	
	public void updateAll(T t) {
		for (CallBack<T> callBack : list) {
			callBack.notify(t);
		}
	}
	
	public void stop() {
		for (CallBack<T> callBack : list) {
			callBack.notifyDeath();
		}
		list.clear();
	}
	
	public void register(CallBack<T> callback) {
		callback.setDispatcher(this);
		list.add(callback);
	}
	
	public void unregister(CallBack<T> callback) {
		list.remove(callback);
	}
}

class CallBack<T>{
	private Dispatcher<T> dispatcher;
	private Consumer<T> notify;
	private Consumer<T> notifyDeath;
	
	public CallBack(Consumer<T> notify, Consumer<T> notifydeath) {
		this.notify = notify;
		this.notifyDeath = notifydeath;
	}
	
	public void notify(T args) {
		notify.accept(args);
	}
	
	public void notifyDeath() {
		notifyDeath.accept(null);
	}
	
	public void unregister() {
		dispatcher.unregister(this);
	}
	
	public void setDispatcher(Dispatcher<T> dispatcher) {
		this.dispatcher = dispatcher;
	}
}

class Client<T>{
	private CallBack<T> callback;
	
	public Client() {
		callback = new CallBack<T>(args->update(args), args->notifyDispatcherDied());
	}
	
	public void update(Object args) {
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
		LocalDateTime now = LocalDateTime.now();
		System.out.println("Receiving message " + "\"" + args + "\"" + " in " + dtf.format(now));
	}
	
	private void notifyDispatcherDied() {
		System.out.println("dispatcher died");
	}
	
	public void unregister() {
		callback.unregister();
	}

	public CallBack<T> getCallBack(){
		return callback;
	}
}

class Producer<T> {
	private  Dispatcher<T> dispatcher;
	
	public Producer() {
		dispatcher = new Dispatcher<>();
	}
	
	public void registerClient(Client<T> client) {
		dispatcher.register(client.getCallBack());
	}
	
	public void stopDispatcher() {
		dispatcher.stop();
	}
	
	public void notifyAll(T args) {
		dispatcher.updateAll(args);
	}
}


