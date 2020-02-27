package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.HashMap;


public class LeetCodeTwoSum {

	public static void main(String[] args) {
		int[] testArr = {3, 3};
		int target = 6;
 		System.out.println(Arrays.toString(twoSum(testArr, target)));
 		System.out.println(Arrays.toString(twoSumMap(testArr, target)));
	}

	public static int[] twoSum(int[] nums, int target) {
		int[] sortedArr = new int [nums.length];
		System.arraycopy(nums, 0, sortedArr, 0, nums.length);
		Arrays.sort(sortedArr);
		int[] result = new int[2];
	    int sum = 0;
	    int i, j, z, k;
	    
		for(i = 0, j = nums.length - 1; i < j;) {
			sum = 0;
			sum = sortedArr[i] + sortedArr[j];
			if(sum > target) {
				--j;
			}
			else if (sum < target) {
				++i;
			}
			else if(sum == target){
				break;
			}
	    }

		if(i == j) {
			return null;
		}
		
		for(k = 0, z = nums.length - 1; ;) {
			if(sortedArr[i] != nums[k]) {
				++k;
			}
			if(sortedArr[j] != nums[z]) {
				--z;
			}
			if(sortedArr[i] == nums[k] && sortedArr[j] == nums[z]) {
				break;
			}
		}
		
	    result[0] = k;
	    result[1] = z;
		
	    return result;
	}

	
	public static int[] twoSumMap(int[] nums, int target){
		int[] result = new int[2];
		HashMap<Integer, Integer> map = new HashMap<>();
		for (int i = 0; i < nums.length; ++i) {
			if(map.containsKey(target - nums[i])) {
				result[0] = map.get(target - nums[i]);
				result[1] = i;
				break;
			}
			else {
				map.put(nums[i], i);
			}
		}
		
	    return result;
	}
}
