package il.co.ilrd.my_tests;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import il.co.ilrd.collections.GenericLinkedList;

class GLLTestJUnit {
	
	GenericLinkedList<Integer> intGLL;
	GenericLinkedList<String> strGLL;
	Integer num1, num2, num3, num4, num5;
	String str1, str2, str3, str4, str5;
	
	@BeforeEach
	void Before() {
		intGLL = new GenericLinkedList<Integer>();
		strGLL = new GenericLinkedList<String>();
		
		num1 = 1;
		num2 = 2;
		num3 = 3;
		num4 = 4;
		num5 = 5;
		
		str1 = "a";
		str2 = "b";
		str3 = "c";
		str4 = "d";
		str5 = "e";
		
		intGLL.pushFront(num1);
		intGLL.pushFront(num2);
		intGLL.pushFront(num3);
		intGLL.pushFront(num4);
		intGLL.pushFront(num5);
		
		strGLL.pushFront(str1);
		strGLL.pushFront(str2);
		strGLL.pushFront(str3);
		strGLL.pushFront(str4);
		strGLL.pushFront(str5);
	}
	
	@Test
	void pushIntTest() {	
		assertEquals(num5, intGLL.popFront());
		assertEquals(num4, intGLL.popFront());
		assertEquals(num3, intGLL.popFront());
		assertEquals(num2, intGLL.popFront());
		assertEquals(num1, intGLL.popFront());
		assertNull(intGLL.popFront());
	}

	@Test
	void pushStrTest() {	
		assertEquals(str5, strGLL.popFront());
		assertEquals(str4, strGLL.popFront());
		assertEquals(str3, strGLL.popFront());
		assertEquals(str2, strGLL.popFront());
		assertEquals(str1, strGLL.popFront());
		assertNull(strGLL.popFront());
	}
	
	
	@Test 
	void findIntTest() {
		assertEquals(num5, intGLL.find(num5).next());
		assertEquals(num4, intGLL.find(num4).next());
		assertEquals(num3, intGLL.find(num3).next());
		assertEquals(num2, intGLL.find(num2).next());
		assertNull(intGLL.find(7));
	}
	
	@Test
	void sizeIntTest() {
		assertEquals(num5, intGLL.getSize());
		intGLL.popFront();
		assertEquals(num4, intGLL.getSize());
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
