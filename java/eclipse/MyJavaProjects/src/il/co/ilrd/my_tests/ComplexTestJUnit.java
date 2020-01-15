package il.co.ilrd.my_tests;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import il.co.ilrd.numerics.*;

class ComplexTestJUnit {

	//1
	@Test
	void testReal() {
		Complex x = new Complex(2.0, 5.0);

		assertEquals(2, x.getReal(), 0.01);
	}

	//2
	@Test
	void testImaginary() {
		Complex x = new Complex(2.0, 5.0);
		
		assertEquals(5, x.getImaginary(), 0.01);
	}
	
	//3
	@Test
	void testParse() {
		Complex x = new Complex(2.0, 4.0);
		Complex y = new Complex(8.0, 4.0);
		
		Complex z = Complex.parseString("8.0+4.0i");
		
		
		assertEquals(z, y);
		assertEquals(x.getImaginary(), y.getImaginary(), 0.01);
	}
	
	//4
	@Test
	void testSet() {
		Complex x = new Complex(2.0, 4.0);
		Complex y = new Complex(8.0, 5.0);
		Complex z = Complex.parseString("8.0+4.0i");
		
		x.setReal(8.0);
		y.setImaginary(4.0);
		
		assertEquals(z, y);
		assertEquals(x, y);
		assertEquals(x, z);
	}
	
	//5
	@Test
	void testNgativeParsing() {
	
		Complex x = new Complex(-8.0, -4.0);
		Complex z = Complex.parseString("-8.0-4.0i");
		
		assertEquals(z, x);
	}
	
	//6
	@Test
	void testCompareTo() {
	
		Complex x = new Complex(-8.0, -4.0);
		Complex z = Complex.parseString("-8.0-4.0i");
		
		assertEquals(0.0, x.compareTo(z), 0.01);
	}
	
	//7
	@Test
	void testCompareToBigger() {
		
		Complex x = new Complex(2.0, 2.0);
		Complex z = Complex.parseString("3.0-2.0i");
		
		
		assertEquals(-2.0, z.getImaginary(), 0.01);
		assertEquals(-5.0, x.compareTo(z), 0.01);
	}
	
	//8
	@Test
	void testParsing() {
		
		Complex exp = new Complex(-3.0, -2.0);
		Complex x = Complex.parseString("-3.0-2.0i");
		Complex z = Complex.parseString("+3.0-2.0i");
		Complex y = Complex.parseString("+3.0-+2.0i");
		
		assertEquals(exp, x);
		assertEquals(null, z);
		assertEquals(null, y);
	}
	
	//9
		@Test
		void testEquals() {
			
			Complex x = Complex.parseString("3.0-2.0i");
			Complex z = Complex.parseString("3.0-2.0i");
			Complex y = Complex.parseString("3.0-2.0i");
			
			assertTrue(x.equals(x));
			
			assertTrue(x.equals(y));
			assertTrue(y.equals(x));
			
			assertTrue(x.equals(y));
			assertTrue(y.equals(z));
			assertTrue(x.equals(z));
			
			assertFalse(x.equals(null));
		}
		

		//10
			@Test
			void testAdd() {
				Complex exp = Complex.parseString("10.5-7.1i");
				
				Complex x = Complex.parseString("3.50-2.3i");
				Complex z = Complex.parseString("3.75-2.3i");
				Complex y = Complex.parseString("3.25-2.5i");
				
			
			assertEquals(exp, x.add(z).add(y));
			}
			
		//11
		@Test
		void testEqualsDouble() {
			
			Complex x = Complex.parseString("3.50+2.3i");
			Complex z = Complex.parseString("3.50+2.3i");
			Complex y = Complex.parseString("3.40+1.3i");
			Complex q = Complex.parseString("0.1+1.0i");
			
			y = y.add(q);

			assertTrue(x.equals(y));
			assertTrue(y.equals(z));
			assertTrue(x.equals(z));
		}
}
