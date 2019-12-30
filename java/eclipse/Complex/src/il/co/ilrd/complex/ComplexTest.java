package il.co.ilrd.complex;

/**
 * 
 */

/**
 * @author student
 *
 */
public class ComplexTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Complex complexNum1 = new Complex(1,2);
		Complex complexNum2 = new Complex(2,3);
		Complex complexNum3 = new Complex(3,4);
		Complex complexNum4 = new Complex(4,5);
		
		complexNum3 = complexNum1.add(complexNum2).substract(complexNum4);
		System.out.println(complexNum3);
		
		complexNum3.setImaginary(5);
		System.out.println(complexNum3);
	}

}
