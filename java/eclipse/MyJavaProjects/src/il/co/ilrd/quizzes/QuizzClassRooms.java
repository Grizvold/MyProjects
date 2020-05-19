package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class QuizzClassRooms {

	public static void main(String[] args) {
		System.out.println(iterative_Solution(new int[] {30, 0, 60}, new int[] {75, 50, 150}));
		System.out.println(hashmap_Solution(new int[] {30, 0, 60}, new int[] {75, 50, 150}));
	}
	
	public static int iterative_Solution(int[] arr_start, int[] arr_end) {
		int num_of_rooms = 0;
		int i = 0, j = 0;
		
		Arrays.sort(arr_start);
		Arrays.sort(arr_end);
		while(i < arr_start.length && j < arr_end.length) {
			if(arr_start[i] <= arr_end[j]) {
				--num_of_rooms;
				++i;
			}
			else {
				++num_of_rooms;
				++j;
			}
		}
		
		return num_of_rooms * -1;
	}

	
	public static int hashmap_Solution(int[] arr_start, int[] arr_end) {
		Map<Integer, Integer> entries = new HashMap<Integer, Integer>();
		Integer num_of_rooms = 0;
		
		for (int i = 0; i < arr_end.length; i++) {
			int start = arr_start[i];
			int end = arr_end[i];
			
			Integer current = entries.get(start);
			entries.put(start, current == null ? 1 : current + 1);
			
			for (Integer entry : entries.values()) {
				num_of_rooms = Math.max(num_of_rooms, entry);
			}

			current = entries.get(end);
			entries.put(end, current == null ? -1 : current - 1);
		}
	
		
		return num_of_rooms;
	}
}
