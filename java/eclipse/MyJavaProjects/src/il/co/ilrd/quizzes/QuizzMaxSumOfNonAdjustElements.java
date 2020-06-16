package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzMaxSumOfNonAdjustElements {

	public static void main(String[] args) {
		int[] arr = new int[] {2, 4, 6, 2, 5};
		System.out.println(Arrays.toString(arr) + " answer is: " + getMaxSum(arr));
		
		arr = new int[] {5, 1, 1, 5};
		System.out.println(Arrays.toString(arr) + " answer is: " + getMaxSum(arr));
		
		arr = new int[] {-2, 0, -3, 0, 14};
		System.out.println(Arrays.toString(arr) + " answer is: " + getMaxSum(arr));
		
		arr = new int[] {2, 4, -6, 2, 5};
		System.out.println(Arrays.toString(arr) + " answer is: " + getMaxSum(arr));
	}
	
	public static int getMaxSum(int[] user_arr) {
		int max_with_element;
		int max_without_element = 0;
		int old_max_with_element;
		
		max_with_element = user_arr[0];
		for (int i = 1; i < user_arr.length; ++i) {
			old_max_with_element = max_with_element; 
			max_with_element = Math.max(max_with_element, user_arr[i] + max_without_element);
			max_without_element = old_max_with_element;
		}
		
		return Math.max(max_with_element, max_without_element);
	}
}
