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
	public V setValue(V value) {
		
		return null;
	}
	
	@Override
	public boolean equals(Object arg0) {
		
		return false;
	}
	
	@Override
	public int hashCode() {
		return 0;
	}
	
	@Override
	public String toString() {
		
		return "key value: " + key + "value: " + val;
	}
	
	public static <K,V> Pair<V, K> swap(K key, V value){
		return null;
	}
	
	public static <K,V> Pair<K, V> of(K key, V value){
		return null;
	}
	
	public static <T> Pair<T, T> minMax(T[] arr){
		return null;
	}
}
