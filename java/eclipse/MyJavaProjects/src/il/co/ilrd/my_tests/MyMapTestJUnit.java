package il.co.ilrd.my_tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import il.co.ilrd.collections.MyMap;

class MyMapTestJUnit {
	
	MyMap<Integer, String> testMap;
	
	@BeforeEach
	void BeforeEach() {
		testMap = new MyMap<Integer, String>();
	}

	@Test
	void testSize() {
		assertEquals(0, testMap.size());
	}
	
	@Test
	void testIsEmpty() {
		assertTrue(testMap.isEmpty());
	}
	
	@Test
	void testPut() {
		testMap.put(1, "a");
		
	}

}
