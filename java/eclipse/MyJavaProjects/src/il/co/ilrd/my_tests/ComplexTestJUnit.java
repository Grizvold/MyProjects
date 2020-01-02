package il.co.ilrd.my_tests;
import il.co.ilrd.numerics.*;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class ComplexTestJUnit {

	@Test
	void testGet() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1.1, 2.2);
		Complex complexNum3 = Complex.parseString("3.2+4.4i");
	
		assertEquals(0.0, complexNum1.getImaginary());
		assertEquals(0.0, complexNum1.getReal());
		assertEquals(1.1, complexNum2.getReal());
		assertEquals(2.2, complexNum2.getImaginary());
		assertEquals(3.2, complexNum3.getReal());
		assertEquals(4.4, complexNum3.getImaginary());
	}
	
	/*@Test
	void testSet() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1,2);
		Complex complexNum3 = Complex.parseString("3+4i");
		
		complexNum1.setImaginary(1);
		assertEquals(1, complexNum1.getImaginary());
		complexNum1.setReal(1);
		assertEquals(1, complexNum1.getReal());
		
		complexNum2.setImaginary(2);
		assertEquals(2, complexNum2.getImaginary());
		complexNum2.setReal(3);
		assertEquals(3, complexNum2.getReal());
		
		complexNum3.setImaginary(5);
		assertEquals(5, complexNum3.getImaginary());
		complexNum3.setReal(7);
		assertEquals(7, complexNum3.getReal());
	}
	
	@Test
	void testAdd() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1,2);
		Complex complexNum3 = Complex.parseString("3+4i");
		Complex complexResult = new Complex();
		
		complexResult = complexNum1.add(complexNum1);
		assertEquals(0, complexResult.getReal());
		assertEquals(0, complexResult.getImaginary());
		
		complexResult = complexNum1.add(complexNum2);
		assertEquals(1, complexResult.getReal());
		assertEquals(2, complexResult.getImaginary());
		
		complexResult = complexNum1.add(complexNum3);
		assertEquals(3, complexResult.getReal());
		assertEquals(4, complexResult.getImaginary());
		
		complexResult = complexNum1.add(complexNum1).add(complexNum2).add(complexNum3);
		assertEquals(4, complexResult.getReal());
		assertEquals(6, complexResult.getImaginary());
		
		complexNum3 = complexNum1.add(complexNum1).add(complexNum2).add(complexNum3);;
		assertEquals(4, complexNum3.getReal());
		assertEquals(6, complexNum3.getImaginary());
	}
	
	@Test
	void testSubstract() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1,2);
		Complex complexNum3 = Complex.parseString("3+4i");
		Complex complexResult = new Complex();
		
		complexResult = complexNum1.substract(complexNum1);
		assertEquals(0, complexResult.getReal());
		assertEquals(0, complexResult.getImaginary());
		
		complexResult = complexNum2.substract(complexNum1);
		assertEquals(1, complexResult.getReal());
		assertEquals(2, complexResult.getImaginary());
		
		complexResult = complexNum1.substract(complexNum3);
		assertEquals(-3, complexResult.getReal());
		assertEquals(-4, complexResult.getImaginary());
		
		complexResult = complexNum1.substract(complexNum2).substract(complexNum3);
		assertEquals(-4, complexResult.getReal());
		assertEquals(-6, complexResult.getImaginary());
		
		complexNum3 = complexNum1.substract(complexNum1).substract(complexNum2).substract(complexNum3);;
		assertEquals(-4, complexNum3.getReal());
		assertEquals(-6, complexNum3.getImaginary());
	}
	
	@Test
	void testEquals() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1,2);
		Complex complexNum3 = Complex.parseString("3+4i");
		
		//Reflexive relation
		assertTrue(complexNum1.equals(complexNum1));
		assertTrue(complexNum2.equals(complexNum2));
		assertTrue(complexNum3.equals(complexNum3));
		
		//Symmetric relation
		complexNum1.setReal(1);
		complexNum1.setImaginary(2);
		assertTrue(complexNum1.equals(complexNum2));
		assertTrue(complexNum2.equals(complexNum1));
		
		//Transitive relation
		complexNum1.setReal(3);
		complexNum1.setImaginary(4);
		complexNum2.setReal(3);
		complexNum2.setImaginary(4);
		assertTrue(complexNum1.equals(complexNum2));
		assertTrue(complexNum2.equals(complexNum3));
		assertTrue(complexNum1.equals(complexNum3));
		
		assertFalse(complexNum1.equals(null));
		assertFalse(complexNum2.equals(null));
		assertFalse(complexNum3.equals(null));
	}
	
	@Test
	void testHash() {
		Complex complexNum1 = new Complex();
		Complex complexNum2 = new Complex(1,2);
		Complex complexNum3 = Complex.parseString("3+4i");
		
		//Multiple invocations
		assertEquals(complexNum1.hashCode(), complexNum1.hashCode());
		assertEquals(complexNum2.hashCode(), complexNum2.hashCode());
		assertEquals(complexNum3.hashCode(), complexNum3.hashCode());
		
		//If equals true -> same hash value
		complexNum1.setReal(1);
		complexNum1.setImaginary(2);
		assertTrue(complexNum1.equals(complexNum2));
		assertTrue(complexNum2.equals(complexNum1));
		assertEquals(complexNum1.hashCode(), complexNum2.hashCode());
		
		complexNum3.setReal(1);
		complexNum3.setImaginary(2);
		assertTrue(complexNum1.equals(complexNum3));
		assertEquals(complexNum1.hashCode(), complexNum3.hashCode());
	}
	
	@Test
	void testParse() {
		Complex complexNum3 = Complex.parseString("3+4i");
		Complex resultComplex = new Complex(3,4);
		
		assertNull(Complex.parseString("+3+4i"));
		assertNull(Complex.parseString("3+4"));
		assertNull(Complex.parseString("3+-4i"));
		assertNull(Complex.parseString("a3+4i"));
		assertNull(Complex.parseString("i"));
		assertTrue(complexNum3.equals(resultComplex));
	}*/
}
