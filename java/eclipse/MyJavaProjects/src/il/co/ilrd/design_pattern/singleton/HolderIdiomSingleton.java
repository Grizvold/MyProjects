package il.co.ilrd.design_pattern.singleton;

public class HolderIdiomSingleton {
	private HolderIdiomSingleton() {};
	
	private static class LazyHolder{
		static final HolderIdiomSingleton instance = new HolderIdiomSingleton();
	}
	
	public static HolderIdiomSingleton getInstance() {
		return LazyHolder.instance;
	}
}

	
