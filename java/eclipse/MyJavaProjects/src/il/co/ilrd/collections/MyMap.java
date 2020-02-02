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
	private static final int numOfBuckets = 16;
	
	public MyMap() {
		hashMap = new ArrayList<LinkedList<Pair<K,V>>>(numOfBuckets);
		
		for (int i = 0; i < numOfBuckets; ++i) {
			hashMap.add(new LinkedList<Pair<K,V>>());
		}
	}
	
	private class EntrySet extends AbstractSet<Entry<K, V>> {

		private class EntryIterator implements Iterator<Entry<K, V>> {
			int currentListIndex = 0;
			Iterator<Pair<K, V>> listIterator = hashMap.get(currentListIndex).iterator();
			
			@Override
			public boolean hasNext() {
				if(listIterator.hasNext()) {
					return true;
				}
				
				for (int i = currentListIndex + 1; i < numOfBuckets; ++i) {
					if(!hashMap.get(i).isEmpty()) {
						return true;
					}
				}
				
				return false;
			}

			@Override
			public Entry<K, V> next() {
				if(!listIterator.hasNext()) {
					
					for (++currentListIndex; currentListIndex < numOfBuckets; ++currentListIndex) {
						if(!hashMap.get(currentListIndex).isEmpty()) {
							listIterator = hashMap.get(currentListIndex).iterator();
							break;
						}
					}
				}
				return listIterator.next();
			}
		}
		
		@Override
		public Iterator<Entry<K, V>> iterator() {
			return new EntryIterator();
		}

		@Override
		public int size() {
			return MyMap.this.size();
		}
	}
	
	private class Values extends AbstractCollection<V> {

		private EntrySet entry = new EntrySet();
		private EntrySet.EntryIterator valIterator = entry.new EntryIterator();
		
		private class ValuesIterator implements Iterator<V> {

			@Override
			public boolean hasNext() {
				return valIterator.hasNext();
			}

			@Override
			public V next() {
				return valIterator.next().getValue();
			}
		}
		
		@Override
		public Iterator<V> iterator() {
			return new ValuesIterator();
		}

		@Override
		public int size() {
			return MyMap.this.size();
		}
	}
	
	private class KeysSet extends AbstractSet<K> {

		private EntrySet entry = new EntrySet();
		private EntrySet.EntryIterator keyIterator = entry.new EntryIterator();
		
		private class KeysIterator implements Iterator<K> {

			@Override
			public boolean hasNext() {
				return keyIterator.hasNext();
			}

			@Override
			public K next() {
				return keyIterator.next().getKey();
			}
		}
		
		@Override
		public Iterator<K> iterator() {
			return new KeysIterator();
		}

		@Override
		public int size() {
			return MyMap.this.size();
		}
	}
	
	@Override
	public void clear() {
		for (LinkedList<Pair<K, V>> linkedList : hashMap) {
			linkedList.clear();
		}
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
		for (LinkedList<Pair<K, V>> linkedList : hashMap) {
			if(!linkedList.isEmpty()) {
				return false;
			}
		}
		return true;
	}

	@Override
	public Set<K> keySet() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public V put(K key, V value) {
		V oldValue = null;
		LinkedList<Pair<K, V>> list = hashMap.get(getIndex(key));
		Pair<K, V> newPair = Pair.of(key, value);
		
		for (Pair<K, V> pair : list) {
			if(pair.getKey().equals(pair.getKey())) {
				oldValue = pair.getValue();
				list.remove(pair);
				break;
			}
		}
		
		list.add(newPair);		
		return oldValue;
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
		int size = 0;
		for (LinkedList<Pair<K, V>> linkedList : hashMap) {
			size += linkedList.size();
		}
		return size;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		return new EntrySet();
	}
	
	@Override
	public Collection<V> values() {
		// TODO Auto-generated method stub
		return null;
	}
	
	private int getIndex(Object key) {
		return key.hashCode() % numOfBuckets;
	}
}