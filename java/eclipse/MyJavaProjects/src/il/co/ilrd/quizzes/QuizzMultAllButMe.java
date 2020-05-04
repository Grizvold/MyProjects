package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzMultAllButMe {

	public static void main(String[] args) {
		System.out.println("Solution by divisio:");
		System.out.println(Arrays.toString(multiplyAllButMe_ByDivision(new int[] {1, 2, 3, 4, 5})));
		System.out.println(Arrays.toString(multiplyAllButMe_ByDivision(new int[] {3, 2, 1})));
		System.out.println(Arrays.toString(multiplyAllButMe_ByDivision(new int[] {10, 7, 5, 3, 2})));
		
		System.out.println("\n" + "Solution without division, by 2 aux arrays:");
		System.out.println(Arrays.toString(multiplyAllButMe_By2Arrays(new int[] {1, 2, 3, 4, 5})));
		System.out.println(Arrays.toString(multiplyAllButMe_By2Arrays(new int[] {3, 2, 1})));
		System.out.println(Arrays.toString(multiplyAllButMe_By2Arrays(new int[] {10, 7, 5, 3, 2})));
		
		System.out.println("\n" + "Solution without division, by 1 aux array + 1 int:");
		System.out.println(Arrays.toString(multiplyAllButMe_By1ArrayAndInt(new int[] {1, 2, 3, 4, 5})));
		System.out.println(Arrays.toString(multiplyAllButMe_By1ArrayAndInt(new int[] {3, 2, 1})));
		System.out.println(Arrays.toString(multiplyAllButMe_By1ArrayAndInt(new int[] {10, 7, 5, 3, 2})));
	}
	
	//time complexity O(n) + O(n)
	public static int[] multiplyAllButMe_ByDivision(int[] user_array) {
		int multiplication_of_array = 1;
		int arr_size = user_array.length;
		int[] result_array = new int[arr_size];
		
		for (int i = 0; i < arr_size; ++i) {
			multiplication_of_array *= user_array[i];
		}
		
		for (int i = 0; i < arr_size; ++i) {
			result_array[i] = multiplication_of_array / user_array[i];
		}
		
		return result_array;
	}
	
	//without using division, using 2 auxiliary arrays, same time complexity O(n) 
	public static int[] multiplyAllButMe_By2Arrays(int[] user_array) {
		int arr_size = user_array.length;
		int[] left_to_right_arr = new int[arr_size];
		int[] right_to_left_arr = new int[arr_size];
		int[] result_arr = new int [arr_size];
		
		left_to_right_arr[0] = user_array[0];
		right_to_left_arr[arr_size - 1] = user_array[arr_size - 1];
		for (int i = 1, j = arr_size - 2; i < arr_size && j >= 0; ++i, --j) {
				left_to_right_arr[i] = left_to_right_arr[i - 1] * user_array[i];
				right_to_left_arr[j] = right_to_left_arr[j + 1] * user_array[j];
		}
		
		result_arr[0] = right_to_left_arr[1];
		result_arr[arr_size - 1] = left_to_right_arr[arr_size - 2];
		for (int i = 1; i < arr_size - 1; ++i) {
			result_arr[i] = left_to_right_arr[i - 1] * right_to_left_arr[i + 1];
		}
		
		return result_arr;
	}
	
	//without using division, using only 1 auxiliary array and 1 integer, time complexity O(n)
	public static int[] multiplyAllButMe_By1ArrayAndInt(int[] user_array) {
		int temp = 1;
		int arr_size = user_array.length;
		int[] result_arr = new int[arr_size];
		int[] right_to_left_arr = new int [arr_size]; 
				
		right_to_left_arr[arr_size - 1] = user_array[arr_size - 1];
		for (int j = arr_size - 2; j >= 0; --j) {
			right_to_left_arr[j] = right_to_left_arr[j + 1] * user_array[j];
		}
		
		result_arr[0] = right_to_left_arr[1];
		for (int i = 0; i < arr_size - 2; ++i) {
			temp *= user_array[i];
			result_arr[i + 1] = temp * right_to_left_arr[i + 2];
		}
		temp *= user_array[arr_size - 2];
		result_arr[arr_size - 1] = temp;
		
		return result_arr;
	}
}
