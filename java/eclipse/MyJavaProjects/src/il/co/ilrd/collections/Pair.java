package il.co.ilrd.collections;

import java.util.Map;

public class Pair<K, V> implements Map.Entry<K, V>{

	private K key;
	private V val;
	
	public Pair(K key, V val) {
		this.key = key;
		this.val = val;
	}
	
	@Override
	public K getKey() {
		return key;
	}

	@Override
	public V getValue() {
		return val;
	}

	@Override
	public V setValue(V newValue) {
		V oldValue = val;
		val = newValue;
		return oldValue;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(null == obj) {
			return false;
		}
		
		if(this == obj) {
			return true;
		}
		
		if(obj instanceof Pair) {
			return (((Pair<?, ?>)obj).key.equals(key) && 
						((Pair<?, ?>)obj).val.equals(val));
		}
		
		return false;
	}
	
	@Override
	public int hashCode() {
		return (key == null ? 0 : key.hashCode()) ^ 
				(val == null ? 0 : val.hashCode());
	}
	
	@Override
	public String toString() {
		
		return "key value: " + key + "value: " + val;
	}
	
	public static <K,V> Pair<V, K> swap(Pair<K, V> pair){
		return new Pair<>(pair.val, pair.key);
	}
	
	public static <K,V> Pair<K, V> of(K key, V value){
		return new Pair<>(key, value);
	}
	
	public static <T extends Comparable<T>> Pair<T, T> minMax(T[] arr){
		T min, max;
		
		min = arr[0];
		max = arr[0];
		
		for (T t : arr) {
			if(t.compareTo(min) < 0) {
				min = t;
			}
			if (t.compareTo(max) > 0) {
				max = t;
			}
		}
		
		return new Pair<T, T>(min, max);
	}
}
