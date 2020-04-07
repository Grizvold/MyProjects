package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzLargestMultiplication {

	public static int maxMultiplicationOf3(int[] arr) {
		int arrayLenght = arr.length;
		Arrays.sort(arr);
		
		return Math.max(arr[0] * arr[1] * arr[arrayLenght - 1], 
						arr[arrayLenght - 1] * arr[arrayLenght - 2] * arr[arrayLenght - 3]);
	}
	
	public static void main(String args[]){

	    int array_1[] = {-10, -10, 5, 2};
	    int array_2[] = {-2, -10, 5, 2};
	    int array_3[] = {-2, -10, 5, 4};
	    int array_4[] = {-2, -10, 5, 4, 3};
	    int array_5[] = {-2, -1, 5, 4, 3};
	    
	    
	    System.out.println(maxMultiplicationOf3(array_1));  
	    System.out.println(maxMultiplicationOf3(array_2));   
	    System.out.println(maxMultiplicationOf3(array_3)); 
	    System.out.println(maxMultiplicationOf3(array_4)); 
	    System.out.println(maxMultiplicationOf3(array_5)); 
	}

}
