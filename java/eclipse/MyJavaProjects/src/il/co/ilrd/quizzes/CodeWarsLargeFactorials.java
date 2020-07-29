package il.co.ilrd.quizzes;

import java.math.BigInteger;
import java.util.stream.IntStream;


public class CodeWarsLargeFactorials {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(Factorial(120));
		System.out.println(Factorial(362880));
}
	
	public static String Factorial(int n) {
		if (n < 2) {
            return "1";
        }
        return IntStream.rangeClosed(2, n).parallel().mapToObj(BigInteger::valueOf).reduce(BigInteger::multiply).get().toString();
	}

}
