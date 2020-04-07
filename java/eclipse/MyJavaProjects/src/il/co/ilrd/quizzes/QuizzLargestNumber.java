package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.Comparator;

public class QuizzLargestNumber {
	
	private class LargerNumberComparator implements Comparator<String>{
		@Override
		public int compare(String a, String b){
			String str1 = a + b;
			String str2 = b + a;
			return str2.compareTo(str1);
		}
	}

	public String largestNumber(int[] nums){
		String[] strOfNums = new String[nums.length];
		for(int i = 0; i < nums.length; ++i){
			strOfNums[i] = String.valueOf(nums[i]);
		}

		Arrays.sort(strOfNums, new LargerNumberComparator());

		//if after sorting largest num '0' -> whole number is 0
		if(strOfNums[0].equals("0")){
			return "0";
		}

		String largestNumber = new String();
		for( String numAsString : strOfNums){
			largestNumber += numAsString;
		}

		return largestNumber;
	}

	public static void main(String[] args) {
		QuizzLargestNumber test1 = new QuizzLargestNumber();
		
		int[] arr1 = {3, 1, 13, 34, 8};
		int[] arr2 = {8, 89, 98, 0};
		System.out.println(test1.largestNumber(arr1));
		System.out.println(test1.largestNumber(arr2));
	}
}
