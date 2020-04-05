package il.co.ilrd.quizzes;

public class QuizzMinumumNumberOfJumps {
	
	public static int minimumJumps(int arr[], int start, int end) {
		if(start == end) {
			return 0;
		}
		
		int minimumJupms = Integer.MAX_VALUE;
		for(int i = start + 1; i <= end && i <= start + arr[start]; ++i) {
			int jumps = minimumJumps(arr, i, end);
			if(jumps != Integer.MAX_VALUE && jumps + 1 < minimumJupms) {
				minimumJupms = jumps + 1;
			}
		}
		
		return minimumJupms;
	}
	
	public static int minJump(int[] arr) {	
		int jumps = 0;
	    int tempMax = 0;
	    int max = 0;

	    for(int i = 0; i < arr.length - 1; ++i) {
	        max = Math.max(max, i + arr[i]);
	        if(i == tempMax) {
	            ++jumps;
	            tempMax = max;
	        } 
	    }
	    
	    return jumps;
	}

	public static void main(String[] args) {
		int arr1[] = {2, 3, 1, 1, 4};
		int arr2[] = {2, 1, 1, 1, 4};
		int arr3[] = {2, 2, 2, 2, 2, 2};
		int arr4[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
		System.out.println("minimum jumps is: " + minimumJumps(arr1, 0, arr1.length - 1));
		System.out.println("minimum jumps is: " + minimumJumps(arr2, 0, arr2.length - 1));
		System.out.println("minimum jumps is: " + minimumJumps(arr3, 0, arr3.length - 1));
		System.out.println("minimum jumps is: " + minimumJumps(arr4, 0, arr4.length - 1));
		
		System.out.println("\nminimum jumps is: " + minJump(arr1));
		System.out.println("minimum jumps is: " + minJump(arr2));
		System.out.println("minimum jumps is: " + minJump(arr3));
		System.out.println("minimum jumps is: " + minJump(arr4));
	}

}
