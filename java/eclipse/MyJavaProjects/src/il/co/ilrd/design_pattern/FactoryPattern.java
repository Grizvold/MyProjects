package il.co.ilrd.design_pattern;

import java.util.HashMap;
import java.util.Map;

public class FactoryPattern<T, K, A> {
	private Map<K, FactoryInterface<T, A>> hashMap = new HashMap<>();
	
	public void add(K key, FactoryInterface<T, A> lambda) {
		hashMap.put(key, lambda);
	}
	
	public T create(K key, A args) {
		if(hashMap.containsKey(key)) {			
			return hashMap.get(key).create(args);
		}
		return null;
	}
}