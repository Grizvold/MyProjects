package il.co.ilrd.design_pattern;

public class LazyInitializationSingleton {
	private static LazyInitializationSingleton instance;
	
	private LazyInitializationSingleton() {};
	
	public static LazyInitializationSingleton getInstance() {
		if(instance == null)
		{
			instance = new LazyInitializationSingleton();
		}
		return instance;
	}
}
