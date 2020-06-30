package il.co.ilrd.quizzes;

import java.util.Arrays;

public class CodeWarsGreedIsGood {

	public static void main(String[] args) {
		System.out.println(greedy(new int[]{5,1,3,4,1}));
		System.out.println(greedy(new int[]{1,1,1,3,1}));
		
		System.out.println("\n" + "\n" + fast_greedy(new int[]{5,1,3,4,1}));
		System.out.println(fast_greedy(new int[]{1,1,1,3,1}));
	}

	/*
		 Three 1's => 1000 points
		 Three 6's =>  600 points
		 Three 5's =>  500 points
		 Three 4's =>  400 points
		 Three 3's =>  300 points
		 Three 2's =>  200 points
		 One   1   =>  100 points
		 One   5   =>   50 point
	*/
	
	public static int fast_greedy(int[] dice){
		int[] dice_values = new int[7];
		for (int dice_roll : dice) {
			++dice_values[dice_roll];
		}
		
		return dice_values[1]/3 * 1000 +
				dice_values[1]%3 * 100 +
				dice_values[2]/3 * 200 +
				dice_values[3]/3 * 300 +
				dice_values[4]/3 * 400 +
				dice_values[5]/3 * 500 +
				dice_values[5]%3 * 50 +
				dice_values[6]/3 * 600;
	}
	
	public static int greedy(int[] dice){
		
		Arrays.sort(dice);
		int points = 0;
		int[] dice_values = new int[7];
		for (int i = 0; i < dice.length; ++i) {
			++dice_values[dice[i]];
		}

		
		while (dice_values[1] != 0) {
			if(dice_values[1] >= 3) {
				points += 1000;
				dice_values[1] -= 3;
			}
			else {
				points += 100;  
				dice_values[1] -= 1;
			}
		}
		
		while (dice_values[5] != 0) {
			if(dice_values[5] >= 3) {
				points += 500;
				dice_values[5] -= 3;
			}
			else {
				points += 50;  
				dice_values[5] -= 1;
			}
		}
		
		while (dice_values[2] != 0) {
			if(dice_values[2] % 3 == 0) {
				points += 200;
				dice_values[2] -= 3;
			}
			else {
				dice_values[2] -= 1;
			}
		}
		
		while (dice_values[3] != 0) {
			if(dice_values[3] % 3 == 0) {
				points += 300;
				dice_values[3] -= 3;
			}
			else {
				dice_values[3] -= 1;
			}
		}
		
		while (dice_values[4] != 0) {
			if(dice_values[4] % 3 == 0) {
				points += 400;
				dice_values[4] -= 3;
			}
			else {
				dice_values[4] -= 1;
			}
		}
	
		while (dice_values[6] != 0) {
			if(dice_values[6] % 3 == 0) {
				points += 600;
				dice_values[6] -= 3;
			}
			else {
				dice_values[6] -= 1;
			}
		}
		
		return points;
	}
}
