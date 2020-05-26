package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class QuizzCandidateSum {

	public static void main(String[] args) {
		combinationSum(new int[] {2, 3, 6, 7}, 7);
	}
	
	public static List<List<Integer>> combinationSum(int[] user_arr, int target){
		List<List<Integer>> result_list = new ArrayList<List<Integer>>();
		int[][] auxiliary_arr = new int[user_arr.length][target + 1];		
		
		Arrays.sort(user_arr);
		
		for (int i = 0; i < user_arr.length; ++i) {
			for (int j = 1; j < target + 1; ++j) {
				auxiliary_arr[i][j] = j / user_arr[i];
			}
		}
		
		for (int[] arr : auxiliary_arr) {
			System.out.println(Arrays.toString(arr));
		}
		
		for (int i = user_arr.length - 1; i >= 0; --i) {
			for (int j = target; j >= 0; --j) {
				int temp_value = auxiliary_arr[i][j] * user_arr[i];
				List<Integer> temp_list = new ArrayList<Integer>();
				if (temp_value == target) {
					temp_list.add(user_arr[i]);
					result_list.add(temp_list);
					break;
				}
				/*if(temp_value < target) {
					int index = i - 1;
					while(temp_value < target) {
						temp_value += auxiliary_arr[i - 1][user_arr[index]] * user_arr[i - 1];
						++index;
					}
					
					
				}*/
			}
		}
			
		System.out.println(result_list);

		return result_list;
	}
	
	public static List<List<Integer>> combinationSum_solution(int[] user_arr, int target){
		List<List<Integer>> result_list = new ArrayList<List<Integer>>();
		
		
		
		return result_list;
	}

}
