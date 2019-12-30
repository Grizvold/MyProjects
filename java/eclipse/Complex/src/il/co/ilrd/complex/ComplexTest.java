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
		Complex testComplex = new Complex(2, 3);
		System.out.println(testComplex);
		Complex resultComplex =  testComplex.add(5);
		System.out.println(resultComplex);
	}

}
