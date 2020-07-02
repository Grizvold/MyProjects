//package il.co.ilrd.my_tests;
//
//import static org.junit.Assert.assertEquals;
//import static org.junit.jupiter.api.Assertions.*;
//import java.util.Optional.*;
//
//import org.junit.jupiter.api.BeforeEach;
//import org.junit.jupiter.api.Test;
//
//import il.co.ilrd.collections.Pair;
//
//class PairTestJUnit {
//
//	Pair<Integer, Integer> intInt1;
//	Pair<Integer, Integer> intInt2;
//	Pair<Integer, Integer> intInt3;
//	Pair<Integer, Integer> intInt4;
//	Pair<Integer, String> intStr1;
//	Pair<Integer, String> intStr2;
//	Pair<Integer, String> intStr3;
//
//	@BeforeEach
//	void beforeEach() {
//		intInt1 = Pair.of(1, 1);
//		intInt2 = Pair.of(2, 2);
//		intInt3 = Pair.of(3, 3);
//		intInt4 = Pair.of(4, 5);
//
//		intStr1 = Pair.of(1, "a");
//		intStr2 = Pair.of(2, "b");
//		intStr3 = Pair.of(3, "c");
//	}
//
//
//	@Test
//	void testGetKey() {
//		assertEquals(1, intInt1.getKey());
//		assertEquals(2, intInt2.getKey());
//		assertEquals(3, intInt3.getKey());
//
//		assertEquals(1, intStr1.getKey());
//		assertEquals(2, intStr2.getKey());
//		assertEquals(3, intStr3.getKey());
//	}
//
//	@Test
//	void testGetValue() {
//		assertEquals(1, intInt1.getValue());
//		assertEquals(2, intInt2.getValue());
//		assertEquals(3, intInt3.getValue());
//
//		assertEquals("a", intStr1.getValue());
//		assertEquals("b", intStr2.getValue());
//		assertEquals("c", intStr3.getValue());
//	}
//
//	@Test
//	void testSwap() {
//		intInt4 = Pair.swap(intInt4);
//		assertEquals(5, intInt4.getKey());
//		assertEquals(4, intInt4.getValue());
//		intInt4 = Pair.swap(intInt4);
//		assertEquals(4, intInt4.getKey());
//		assertEquals(5, intInt4.getValue());
//	}
//
//	@Test
//	void testOf() {
//		intInt4 = Pair.of(5, 10);
//		assertEquals(5, intInt4.getKey());
//		assertEquals(10, intInt4.getValue());
//		intInt4 = Pair.of(10, 5);
//		assertEquals(10, intInt4.getKey());
//		assertEquals(5, intInt4.getValue());
//	}
//
//}
