package il.co.ilrd.quizzes;

import java.util.Arrays;

public class CodeWarsTribonacciSequence {

	public static void main(String[] args) {
		System.out.println(Arrays.toString(tribonacci(new double[] {1, 1, 1}, 10)));
		System.out.println(Arrays.toString(tribonacci(new double[] {0, 0, 1}, 10)));
		System.out.println(Arrays.toString(tribonacci(new double[] {1, 1, 1}, 4)));
	}
	
	public static double[] tribonacci(double[] s, int n) {
//		double[] results = new double[n];
//		double num_1 = 0;
//		double num_2 = 0;
//		double num_3 = 0;
//		double num_4 = 0;
//		
//		if (n <= 3) {
//			switch (n) {
//			case 0:
//				return results;
//			case 1:
//				results[0] = s[0];
//				return results;
//			case 2:
//				results[0] = s[0];
//				results[1] = s[1];
//				return results;
//			case 3:
//				results[0] = s[0];
//				results[1] = s[1];
//				results[2] = s[2];
//				return results;
//			default:
//				break;
//			}
//		}
//		
//		num_1 = results[0] = s[0];
//		num_2 = results[1] = s[1];
//		num_3 = results[2] = s[2];
//		for (int i = 3; i < n; ++i) {
//			num_4 = num_1 + num_2 + num_3;
//			num_1 = num_2;
//			num_2 = num_3;
//			num_3 = num_4;
//			results[i] = num_4; 
//		}
		double[] results = Arrays.copyOf(s, n);
		
		for (int i = 3; i < results.length; i++) {
			results[i] = results[i - 1] + 
							results[i - 2] + 
							results[i - 3];
		}
		
		return results;
	}
}
