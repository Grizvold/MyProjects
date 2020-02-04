package il.co.ilrd.design_pattern.singleton;

public class EagerInitializationSingleton {
	private static final EagerInitializationSingleton instance = new EagerInitializationSingleton();
	
	private EagerInitializationSingleton() {};
	
	public static EagerInitializationSingleton getInstance() {
		return instance;
	}
}
