package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.stream.IntStream;

import com.sun.org.apache.bcel.internal.generic.NEW;

import sun.security.util.Length;

public class DailyCode_ArraySplitsToTwoEqualArrays {
	
	public static void main(String[] args) {
		System.out.println(isPartitioned(new int[] {5,10,15,10,20,15,35}));
        System.out.println(isPartitioned(new int[] {5,10,15,10,20,10,40}));
        System.out.println(isPartitioned(new int[] {1,2,3}));
        System.out.println(isPartitioned(new int[] {7,3,4,2}));
        System.out.println(isPartitioned(new int[] {100,150,32,14,4}));
        System.out.println(isPartitioned(new int[] {1,0,3}));
        System.out.println(isPartitioned(new int[] {1, 10, 7, 3}));
        System.out.println(isPartitioned(new int[] {0, 10, 7, 3}));
        
        System.out.println("\nfinding marker");
        int resultOfMarker;
        System.out.println(resultOfMarker = findMark(new int[] {1, 2, 1}));
        System.out.println(resultOfMarker = findMark(new int[] {1, 2, 5, 2, 1}));
        System.out.println(resultOfMarker = findMark(new int[] {1, 2, 2, 1}));
        System.out.println(resultOfMarker = findMark(new int[] {1, 2, 3, 3, 2, 1}));
        System.out.println(resultOfMarker = findMark(new int[] {1, 2, 3, 4, 2, 1}));
	}
	
	public static int findMark(int arr[]) {
		
		int leftSum = arr[0], rightSum = arr[arr.length - 1];
		
		for (int i = 0, j = arr.length - 1; i < j;) {
			
			leftSum += arr[i];
			rightSum += arr[j];

			if(leftSum < rightSum) {				
				++i;
			}
			else if (leftSum > rightSum) {
				--j;
			}
			else if (leftSum == rightSum) {
				if(i + 1 == j) {
					return i;
				}
				else if (i + 2 == j) {
					return i + 1;
				}
				else {
					++i;
					--j;
				}
			}
		}
		//false return
		return -1;
	}
	
	public static boolean isPartitioned(int arr[]) {
		Arrays.sort(arr);
		
		if((IntStream.of(arr).sum()) % 2 != 0) {
			return false;
		}
		
		int halfOfSum = IntStream.of(arr).sum() / 2;
		
		int tempSum = 0;
		for (int j = arr.length - 1; j >= 0; --j) {
			tempSum += arr[j];
			
			if (tempSum > halfOfSum) {
				tempSum -= arr[j];
			}
			
			if(tempSum == halfOfSum) {
				return true;
			}
		}
		
		return false;
	}
}
