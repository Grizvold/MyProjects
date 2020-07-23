package il.co.ilrd.quizzes;

import java.math.BigInteger;
import java.util.Arrays;

public class CodeWarsGapInPrimes {

	public static void main(String[] args) {
		System.out.println(Arrays.toString(gap(2, 3, 50)));
		System.out.println(Arrays.toString(gap(2,100,110)));
		System.out.println(Arrays.toString(gap(4,100,110)));
		System.out.println(Arrays.toString(gap(8,300,400)));
		System.out.println(Arrays.toString(gap(10,300,400)));
		
	}

	public static long[] gap(int g, long m, long n) {
        long[] result = new long[2];
        
        for (long i = m; i <= n; ++i) {
			BigInteger first_num = new BigInteger(String.valueOf(i));
			if(first_num.isProbablePrime(1)){
				BigInteger second_num = new BigInteger(String.valueOf(i + g));
				if(second_num.isProbablePrime(1) && i + g <= n ) {
					BigInteger in_between = new BigInteger(String.valueOf(i));
					long j = i + 1;
					for (; j < i + g; ++j) {
						in_between = new BigInteger(String.valueOf(j));
						if(in_between.isProbablePrime(1)) {
							break;
						}
					}
					if((j == i + g)) {
						result[0] = i;
						result[1] = i + g;
						return result;
					}			
				}
			}				
        }
        return null;
	}
}