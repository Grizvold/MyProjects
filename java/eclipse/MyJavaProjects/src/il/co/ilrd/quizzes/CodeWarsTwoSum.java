package il.co.ilrd.quizzes;

import java.util.Arrays;

public class CodeWarsTwoSum {

	public static void main(String[] args) {
		System.out.println(Arrays.toString(twoSum(new int[] {1, 2, 3}, 4)));
	}
	
	public static int[] twoSum(int[] numbers, int target) {
		int[] indexes = new int[2];
		
		Arrays.sort(numbers);
		for (int i = 0, j = numbers.length - 1; i < j;) {
			if ((numbers[i] + numbers[j]) == target) {
				indexes[0] = i;
				indexes[1] = j;
				return indexes;
			}
			else if ((numbers[i] + numbers[j]) > target) {
				--j;
			}
			else {
				++i;
			}
		}
		
        return null; 
    }

}
