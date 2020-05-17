package il.co.ilrd.quizzes;

import java.util.HashSet;
import java.util.Set;

public class QuizzLongestSubstringWithKUniqueChars {

	public static void main(String[] args) {
		System.out.println("abcba, k = 2. Result: " + longest_substring_with_k_distinct_characters("abcba", 2));
		System.out.println("abcba, k = 3. Result: " + longest_substring_with_k_distinct_characters("abcba", 3));
		System.out.println("abbbbbbbcba, k = 1. Result: " + longest_substring_with_k_distinct_characters("abbbbbbbcba", 1));
	}

	
	public static String longest_substring_with_k_distinct_characters(String inputString, int k){
		int start_index = 0, stop_index = 0;
		int[] count_arr = new int[128]; //characters range
		Set<Character> substringSet = new HashSet<Character>();
		
		for (int low = 0, high = 0; high < inputString.length(); ++high) {
			substringSet.add(inputString.charAt(high));
			++count_arr[inputString.charAt(high)]; 
		
			//removing characters from the left
			while (substringSet.size() > k) {
				//if most left char is 0 -> remove it from set
				if(--count_arr[inputString.charAt(low)] == 0) {
					substringSet.remove(inputString.charAt(low));
				}
				
				++low;
			}
			
			if (stop_index - start_index < high - low) {
				start_index = low;
				stop_index = high;
			}
		}
		
		return inputString.substring(start_index, stop_index + 1);
	}
}
