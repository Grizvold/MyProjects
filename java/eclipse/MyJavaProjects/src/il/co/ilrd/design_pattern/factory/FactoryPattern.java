package il.co.ilrd.design_pattern.factory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class FactoryPattern<T, K, A> {
	private Map<K, Function<A, T>> hashMap = new HashMap<>();
	
	public void add(K key, Function<A, T> lambda) {
		hashMap.put(key, lambda);
	}
	
	public T create(K key, A args) {		
		return hashMap.get(key).apply(args);
	}
}