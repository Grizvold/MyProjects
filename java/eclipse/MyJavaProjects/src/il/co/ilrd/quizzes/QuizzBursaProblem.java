package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzBursaProblem {

	public static void main(String[] args) {
		System.out.println(String.format("Testing solutions for bursa problem:" + 
						"\nFor {11, 8, 9, 5, 7, 10} result: %s" + 
						"\nFor {7, -7, 1, 1, 7, 1} result: %s", 
						Arrays.toString(bursa_problem(new int[] {11, 8, 9, 5, 7, 10})),
						Arrays.toString(bursa_problem(new int[] {7, -7, 1, 1, 7, 1}))));
	}
	
	public static int[] bursa_problem(int[] user_arr) {
		int buy_index = 0, sell_index = 0;
		int max_profit = 0, temp_profit = 0;
		
		for (int i = 0; i < user_arr.length; ++i) {
			if(user_arr[i] < user_arr[buy_index]) {
				buy_index = i;
			}
			
			temp_profit = user_arr[i] - user_arr[buy_index];
			
			if(temp_profit > max_profit) {
				max_profit = temp_profit;
				sell_index = i;
			}
		}
		
		return new int[] {buy_index, sell_index, max_profit};
	}

}
