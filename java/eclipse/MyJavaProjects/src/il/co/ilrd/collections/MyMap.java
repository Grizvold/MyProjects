package il.co.ilrd.collections;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;


public class MyMap<K, V> implements Map<K, V>{
	
	private ArrayList<LinkedList<Pair<K, V>>> hashMap;
	private static final int size = 16;
	
	public MyMap() {
		hashMap = new ArrayList<LinkedList<Pair<K,V>>>(size);
	}
	
	private class EntrySet extends AbstractSet<Pair<K, V>> {

		private class EntryIterator implements Iterator<Pair<K, V>> {

			@Override
			public boolean hasNext() {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public Pair<K, V> next() {
				// TODO Auto-generated method stub
				return null;
			}
		}
		
		@Override
		public Iterator<Pair<K, V>> iterator() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public int size() {
			// TODO Auto-generated method stub
			return 0;
		}
	}
	
	private class Values extends AbstractCollection<V> {

		private EntrySet entry = new EntrySet();
		
		private class ValuesIterator implements Iterator<V> {

			@Override
			public boolean hasNext() {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public V next() {
				// TODO Auto-generated method stub
				return null;
			}
		}
		
		@Override
		public Iterator<V> iterator() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public int size() {
			// TODO Auto-generated method stub
			return 0;
		}
	}
	
	private class KeysSet extends AbstractSet<K> {

		private EntrySet entry = new EntrySet();
		
		private class KeysIterator implements Iterator<K> {

			@Override
			public boolean hasNext() {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public K next() {
				// TODO Auto-generated method stub
				return null;
			}
		}
		
		@Override
		public Iterator<K> iterator() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public int size() {
			// TODO Auto-generated method stub
			return 0;
		}
	}
	
	@Override
	public void clear() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean containsKey(Object key) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public V get(Object key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public Set<K> keySet() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public V put(K key, V value) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public V remove(Object key) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public Collection<V> values() {
		// TODO Auto-generated method stub
		return null;
	}
}