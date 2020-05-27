package il.co.ilrd.quizzes;

import il.co.ilrd.collections.Pair;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class DailyCode100_FindShortestPath2DMatrix {

	public static void main(String[] args) {
		List<Pair<Integer, Integer>> pair_sequenceList = new ArrayList<Pair<Integer,Integer>>();
		pair_sequenceList.add(Pair.of(0,0));
		pair_sequenceList.add(Pair.of(1,1));
		pair_sequenceList.add(Pair.of(1,2));
		System.out.println(getNumberOfSteps(pair_sequenceList));
		
		pair_sequenceList.clear();
		pair_sequenceList.add(Pair.of(0,0));
		pair_sequenceList.add(Pair.of(1,1));
		pair_sequenceList.add(Pair.of(2,3));
		System.out.println(getNumberOfSteps(pair_sequenceList));
		
		pair_sequenceList.clear();
		pair_sequenceList.add(Pair.of(0,0));
		pair_sequenceList.add(Pair.of(1,3));
		pair_sequenceList.add(Pair.of(2,0));
		System.out.println(getNumberOfSteps(pair_sequenceList));
		
		pair_sequenceList.clear();
		pair_sequenceList.add(Pair.of(0,0));
		pair_sequenceList.add(Pair.of(2,3));
		pair_sequenceList.add(Pair.of(0,3));
		pair_sequenceList.add(Pair.of(0,1));
		System.out.println(getNumberOfSteps(pair_sequenceList));
	}

	public static int getNumberOfSteps(List<Pair<Integer, Integer>> user_sequence) {
		int number_of_steps = 0;
		int x_difference = 0, y_difference= 0;
		Pair<Integer, Integer> current_point = user_sequence.get(0);
		
		for (Pair<Integer, Integer> pair : user_sequence) {
			while (current_point.getKey() != pair.getKey() || current_point.getValue() != pair.getValue()) {
				x_difference = Math.abs(current_point.getKey() - pair.getKey());
				y_difference = Math.abs(current_point.getValue() - pair.getValue());
				
				//x is same but y different
				if(current_point.getKey() == pair.getKey()) {
					number_of_steps += Math.abs(pair.getValue() - current_point.getValue());
					current_point = Pair.of(pair.getKey(), pair.getValue());
				}
				//x not the same but y can be same or not
				else {
					if(x_difference > 1) {
						if(y_difference <= 1) {
							number_of_steps += Math.abs(pair.getKey() - current_point.getKey());
							current_point = Pair.of(pair.getKey(), pair.getValue());
						}
						//y difference > 1
						else {
							number_of_steps += Math.abs(pair.getValue() - current_point.getValue());
							current_point = Pair.of(pair.getKey(), pair.getValue());
						}
					}
					else if(x_difference == 1){
						if(y_difference <= 1) {
							number_of_steps += 1;
							current_point = Pair.of(pair.getKey(), pair.getValue());
						}
						//y difference > 1
						else {
							number_of_steps += Math.abs(pair.getValue() - current_point.getValue());
							current_point = Pair.of(pair.getKey(), pair.getValue());
						}
					}
				}
			}
		}
	
		System.out.println(Arrays.toString(user_sequence.toArray()));
		
		return number_of_steps;
	}
}