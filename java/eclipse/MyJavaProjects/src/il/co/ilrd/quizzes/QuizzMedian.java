package il.co.ilrd.quizzes;

import java.util.LinkedList;
import java.util.List;

public class QuizzMedian {
	private static 	List<Integer> sequence_list = new LinkedList<Integer>();

	public static void main(String[] args) {
		System.out.println("Tests for median:");
		System.out.println("inserting 1 -> Mediam: " + add_Node_Tolist(1) + ", List: " + sequence_list);
		System.out.println("inserting 2 -> Mediam: " + add_Node_Tolist(2) + ", List: " + sequence_list);
		System.out.println("inserting 3 -> Mediam: " + add_Node_Tolist(3) + ", List: " + sequence_list);
		System.out.println("inserting 2 -> Mediam: " + add_Node_Tolist(2) + ", List: " + sequence_list);
		System.out.println("inserting 0 -> Mediam: " + add_Node_Tolist(0) + ", List: " + sequence_list);
		System.out.println("inserting 10 -> Mediam: " + add_Node_Tolist(10) + ", List: " + sequence_list);
	}

	public static int add_Node_Tolist(int input_num) {
		for (int i = 0; i < sequence_list.size(); ++i) {
			if(input_num <= sequence_list.get(i)) {
				sequence_list.add(i, input_num);
				return get_Median(sequence_list);
			}
		}
		//first input
		sequence_list.add(input_num);
		return get_Median(sequence_list);
	}
	
	private static int get_Median(List<Integer> user_list) {
		int median = 0;
		
		if(user_list.size() % 2 == 0) {
			int first_value = user_list.get(user_list.size() / 2);
			int second_value = user_list.get(user_list.size() / 2 - 1);
			median = (first_value + second_value) / 2;
		}
		
		else {
			median = user_list.get(user_list.size() / 2);
		}
		
		return median;
	}
}
