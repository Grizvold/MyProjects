package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzSortOddNumbers {

	public static void main(String[] args) {
		System.out.println(String.format("Tests for naive solution:\n" 
				+ "5 3 2 8 1 4 -> %s\n"
				+ "1 2 3 8 1 4 -> %s\n",
				Arrays.toString(sortOddNumbers_naive(new int[] {5, 3, 2, 8, 1, 4})),
				Arrays.toString(sortOddNumbers_naive(new int[] {0, 2, 3, 8, 1, 4}))));
	}

	public static int[] sortOddNumbers_naive(int[] user_array) {
		if(user_array.length == 0) {
			return user_array;
		}
		
		int oddNum_cout = 0;
		for (int i = 0; i < user_array.length; ++i) {
			if(user_array[i] % 2 != 0) {
				++oddNum_cout;
			}
		}
		
		int oddNum_array[] = new int[oddNum_cout];
		for (int i = 0, j = 0; i < user_array.length && j < oddNum_array.length; ++i) {
			if(user_array[i] % 2 != 0) {
				oddNum_array[j] = user_array[i];
				++j;
			}
		}
		Arrays.sort(oddNum_array);
		
		for (int i = 0, j = 0; i < user_array.length && j < oddNum_array.length; ++i, ++j) {
			while(user_array[i] % 2 == 0) {
				++i;
			}
			
			user_array[i] = oddNum_array[j];
		}
		
		return user_array;
	}
}
