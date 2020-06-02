package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzAllButOne {

	public static void main(String[] args) {
		System.out.println(Arrays.toString(allButOne_byDevision(new int[] {1, 2, 3, 4, 5})));
		
		System.out.println(Arrays.toString(allButOne_by2AuxilaryArrays(new int[] {1, 2, 3, 4, 5})));
		
		System.out.println(Arrays.toString(allButOne_by1AuxilaryArrayAnd1Int(new int[] {1, 2, 3, 4, 5})));
	}

	
	public static int[] allButOne_byDevision(int[] user_arr) {
		int[] result_arr = new int[user_arr.length];
		int multiplication = 1;
		
		for (int i = 0; i < result_arr.length; ++i) {
			multiplication *= user_arr[i];
		}
		
		for (int i = 0; i < result_arr.length; ++i) {
			result_arr[i] = multiplication / user_arr[i];
		}
		
		return result_arr;
	}
	
	public static int[] allButOne_by2AuxilaryArrays(int[] user_arr) {
		int[] left_to_right_arr = new int[user_arr.length];
		int[] right_to_left_arr = new int[user_arr.length];
		int[] result_arr = new int[user_arr.length];
		
		left_to_right_arr[0] = user_arr[0];
		for (int i = 1; i < result_arr.length; i++) {
			left_to_right_arr[i] = left_to_right_arr[i - 1] * user_arr[i];
		}
		
		right_to_left_arr[user_arr.length - 1] = user_arr[user_arr.length - 1];
		for (int i = user_arr.length - 2; i >= 0; --i) {
			right_to_left_arr[i] = right_to_left_arr[i + 1] * user_arr[i];
		}
		
		result_arr[0] = right_to_left_arr[1];
		result_arr[user_arr.length - 1] = left_to_right_arr[user_arr.length - 2];
		for (int i = 1; i < result_arr.length - 1; i++) {
			result_arr[i] = left_to_right_arr[i - 1] * right_to_left_arr[i + 1];
		}
		
		return result_arr;
	}
	
	public static int[] allButOne_by1AuxilaryArrayAnd1Int(int[] user_arr) {
		int[] right_to_left_arr = new int[user_arr.length];
		int[] result_arr = new int[user_arr.length];
		int temp = 1;
		
		right_to_left_arr[user_arr.length - 1] = user_arr[user_arr.length - 1];
		for (int i = user_arr.length - 2; i >= 0; --i) {
			right_to_left_arr[i] = right_to_left_arr[i + 1] * user_arr[i];
		}
		
		result_arr[0] = right_to_left_arr[1];
		for (int i = 0; i < result_arr.length - 2; i++) {
			temp *= user_arr[i];
			result_arr[i + 1] = temp * right_to_left_arr[i + 2];
		}
		temp *= user_arr[user_arr.length -2];
		result_arr[user_arr.length -1] = temp;
		
		return result_arr;
	}
}
