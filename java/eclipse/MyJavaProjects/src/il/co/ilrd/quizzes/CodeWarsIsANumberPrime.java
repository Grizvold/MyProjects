package il.co.ilrd.quizzes;

public class CodeWarsIsANumberPrime {

	public static void main(String[] args) {
		System.out.println(isPrime(0));
		System.out.println(isPrime(1));
		System.out.println(isPrime(2));
		System.out.println(isPrime(4));
		System.out.println(isPrime(9));
		System.out.println(isPrime(7));
		
		System.out.println("\none line solution: \n" + isPrime_v2(0));
		System.out.println(isPrime_v2(1));
		System.out.println(isPrime_v2(2));
		System.out.println(isPrime_v2(4));
		System.out.println(isPrime_v2(9));
		System.out.println(isPrime_v2(7));
	}

	public static boolean isPrime(int num) {
		if(num <= 1) {
			return false;
		}
		
		for (int i = 2; i <= Math.sqrt(num); i++) {
			if(num % i == 0) {
				return false;
			}
		}
		
		return true; 
	}
	
	public static boolean isPrime_v2(int num) {
		return num > 1 && java.math.BigInteger.valueOf(num).isProbablePrime(20);
	}
}
