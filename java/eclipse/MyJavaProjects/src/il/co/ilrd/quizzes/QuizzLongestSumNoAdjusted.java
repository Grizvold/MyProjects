package il.co.ilrd.quizzes;

public class QuizzLongestSumNoAdjusted {

	public static void main(String[] args) {
		System.out.println(get_MaxSum(new int[] {2, 4, 6, 2, 5}));
		System.out.println(get_MaxSum(new int[] {5, 1, 1, 5}));
	}
	
	public static int get_MaxSum(int[] user_arr) {
		return Math.max(recursive_MaxSum(user_arr, 0, 0), recursive_MaxSum(user_arr, 1, 0));
	}
	
	private static int recursive_MaxSum(int[] user_arr, int index, int sum) {
		if(index >= user_arr.length - 2) {
			if(index < user_arr.length) {
				return sum > sum + user_arr[index] ? sum : sum + user_arr[index];
			}
			else {
				return sum;
			}
		}
		
		if (sum < sum + user_arr[index]) {
			sum += user_arr[index];
		}
		
		int sum_jumps_by_2 = recursive_MaxSum(user_arr, index + 2, sum);
		int sum_jumps_by_3= recursive_MaxSum(user_arr, index + 3, sum);
		
		return Math.max(sum_jumps_by_2, sum_jumps_by_3);
	}
}
