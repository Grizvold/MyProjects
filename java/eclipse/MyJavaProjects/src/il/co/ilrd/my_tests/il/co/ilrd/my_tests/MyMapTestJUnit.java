package il.co.ilrd.my_tests;


import java.util.Iterator;
import il.co.ilrd.collections.MyMap;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class MyMapTestJUnit {
	
	MyMap<Integer, String> testMap;
	
	@BeforeEach
	void BeforeEach() {
		testMap = new MyMap<Integer, String>();
		testMap.put(1, "a");
		testMap.put(2, "b");
		testMap.put(3, "c");
		testMap.put(17, "d");
		testMap.put(18, "e");
	}

	@Test
	void testSize() {
		assertEquals(5, testMap.size());
		
		testMap.put(18, "f");
		assertEquals(5, testMap.size());
	}
	
	@Test
	void testIsEmpty() {
		testMap.clear();
		assertTrue(testMap.isEmpty());
		testMap.put(1, "a");
		assertFalse(testMap.isEmpty());
	}
	
	@Test
	void testPutAndGet() {
		String expected[] = {"a", "b", "c", "d", "e"};
		Integer keys[] = {1, 2, 3, 17, 18};
		for (int i = 0; i < expected.length; ++i) {
			assertEquals(expected[i], testMap.get(keys[i]));
		}
				
		assertNull(testMap.get(6));
		testMap.put(5, "f");
		assertEquals("f", testMap.get(5));
	}
	
	@Test
	void testValues() {
		String expected[] = {"a", "d", "b", "e", "c"};

		Iterator<String> valuesIterator = testMap.values().iterator();
		for (int i = 0; i < expected.length; ++i) {
			assertEquals(expected[i], valuesIterator.next());
		}
	}
	
	@Test
	void testKeysSet() {
		Integer keys[] = {1, 17, 2, 18, 3};
		
		Iterator<Integer> keysIterator = testMap.keySet().iterator();
		for (int i = 0; i < keys.length; ++i) {
			assertEquals(keys[i], keysIterator.next());
		}
	}
	
	@Test
	void testContainsKey() {
		assertTrue(testMap.containsKey(1));
		assertTrue(testMap.containsKey(17));
		assertTrue(testMap.containsKey(2));
		assertTrue(testMap.containsKey(18));
		assertTrue(testMap.containsKey(3));
		assertFalse(testMap.containsKey(4));
		assertFalse(testMap.containsKey(5));
	}
	
	@Test
	void testContainsValue() {
		assertTrue(testMap.containsValue("a"));
		assertTrue(testMap.containsValue("b"));
		assertTrue(testMap.containsValue("c"));
		assertFalse(testMap.containsValue("r"));
		assertFalse(testMap.containsValue("v"));
	}
	
	@Test
	void testPutAll() {
		MyMap<Integer, String> secondMap = new MyMap<Integer, String>();
		secondMap.put(5, "a");
		secondMap.put(6, "a");
		secondMap.put(7, "a");
		secondMap.put(19, "a");
		secondMap.put(1, "a");
		testMap.putAll(secondMap);
		assertEquals(9, testMap.size());
	}

	@Test
	void testRemove() {
		testMap.remove(1);
		assertEquals(4, testMap.size());
		testMap.remove(18);
		assertEquals(3, testMap.size());
	}
}
