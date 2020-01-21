package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizSortAndTripletRuslanGorbaty 
{
	public static void sortArray(int[] arr)
	{
		int temp = 0;
		for (int i = 0, j = arr.length - 1; i < j; ++i, --j) 
		{
			while(1 == arr[j])
			{
				--j;
			}
			
			while(0 == arr[i])
			{
				++i;
			}
			
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	
	public static boolean isTripletSum(int[] arr, int num)
	{	
		Arrays.sort(arr);
	
		for (int firstElem = 0; firstElem < arr.length - 2; ++firstElem) 
		{
			int secondElem = firstElem + 1;
			int thirdElem = arr.length - 1;
			while(secondElem < thirdElem)
			{
				int sum = arr[firstElem] + arr[secondElem] + arr[thirdElem];
				if(num == sum)
				{
					return true;
				}
				else if(num > sum) 
				{
					++secondElem;
				}
				else
				{
					/* num < sum */
					--thirdElem;
				}
			}
		}
		
		return false;
	}
		
	public static void main(String[] args) 
	{
		int[] testArray1 = {0,1,0,1,0,0,1};
		int[] testArray2 = {0,1,1,1,0,0,0};
		System.out.println("Array 1 before sorting: " + Arrays.toString(testArray1));
		System.out.println("Array 2 before sorting: " + Arrays.toString(testArray2));
		sortArray(testArray1);
		sortArray(testArray2);
		System.out.println("Array 1 after sorting: " + Arrays.toString(testArray1));
		System.out.println("Array 2 after sorting: " + Arrays.toString(testArray2));
		
		int[] testArray3 = {1,3,5,2,7,10,6};
		int testSum = 16;
		System.out.println("\nIs there triplet that gives desired sum: " + isTripletSum(testArray3, testSum));
	}
}
