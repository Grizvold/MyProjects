package il.co.ilrd.my_tests;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import il.co.ilrd.collections.GenericLinkedList;

class GLLTestJUnit {
	
	GenericLinkedList<Integer> intGLL;
	GenericLinkedList<String> strGLL;
	String[] strArray = {"a", "b", "c", "d", "e"};
	int[] intArray =  {1, 2, 3, 4, 5};
	
	
	@BeforeEach
	void Before() {
		intGLL = new GenericLinkedList<Integer>();
		strGLL = new GenericLinkedList<String>();

		for (int i = 0; i < 5; ++i) {
			intGLL.pushFront(intArray[i]);
			strGLL.pushFront(strArray[i]);
		}

	}
	
	@Test
	void pushIntTest() {	
		assertEquals(intArray[4], intGLL.popFront());
		assertEquals(intArray[3], intGLL.popFront());
		assertEquals(intArray[2], intGLL.popFront());
		assertEquals(intArray[1], intGLL.popFront());
		assertEquals(intArray[0], intGLL.popFront());
		assertNull(intGLL.popFront());
	}

	@Test
	void pushStrTest() {	
		assertEquals(strArray[4], strGLL.popFront());
		assertEquals(strArray[3], strGLL.popFront());
		assertEquals(strArray[2], strGLL.popFront());
		assertEquals(strArray[1], strGLL.popFront());
		assertEquals(strArray[0], strGLL.popFront());
		assertNull(strGLL.popFront());
	}
	
	
	@Test 
	void findIntTest() {
		assertEquals(intArray[4], intGLL.find(intArray[4]).next());
		assertEquals(intArray[3], intGLL.find(intArray[3]).next());
		assertEquals(intArray[2], intGLL.find(intArray[2]).next());
		assertEquals(intArray[1], intGLL.find(intArray[1]).next());
		assertNull(intGLL.find(7));
	}
	
	@Test
	void sizeIntTest() {
		assertEquals(intArray[4], intGLL.getSize());
		intGLL.popFront();
		assertEquals(intArray[3], intGLL.getSize());
		assertFalse(intGLL.isEmpty());
	}
	
	@Test 
	void sizeStrTest() {
		assertEquals(5, strGLL.getSize());
		strGLL.popFront();
		assertEquals(4, strGLL.getSize());
		assertFalse(strGLL.isEmpty());
	}
}
