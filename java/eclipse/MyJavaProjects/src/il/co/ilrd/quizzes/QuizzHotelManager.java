package il.co.ilrd.quizzes;

import java.util.Arrays;

public class QuizzHotelManager {

	public static void main(String[] args) {
		System.out.println(hotel_Manager(new int[] {1, 3, 5}, new int[] {2, 6, 10}, 1));
		System.out.println(hotel_Manager(new int[] {1, 3, 5}, new int[] {2, 4, 6}, 1));
		
		System.out.println(get_Max_wf(new int[] {1, 2, 3, 4, 7}, new int[] {4, 6, 7, 5, 10}));
		System.out.println(get_Max_wf(new int[] {1, 2, 4, 5, 7}, new int[] {4, 6, 6, 7, 10}));
		System.out.println(get_Max_wf(new int[] {0, 1, 3, 4, 7}, new int[] {2, 5, 7, 6, 8}));
		System.out.println(get_Max_wf(new int[] {0, 3, 4, 7, 1}, new int[] {2, 7, 6, 8, 5}));
	}

	public static boolean hotel_Manager(int arrival[], int departure[], int rooms) {
		int i = 0, j = 0;
		while(i < arrival.length && j < departure.length) {
			if(arrival[i] <= departure[j]) {
				--rooms;
				++i;
				if(rooms < 0) {
					return false;
				}
			}
			else {
				++rooms;
				++j;
			}
		}
		
		return true;
	}
	
	public static int get_Max_wf(int start[], int end[]) {
		int max_wf = 0;
		int count_wf = 0;
		
		Arrays.sort(start);
		Arrays.sort(end);
		for (int i = 0, j = 0; i < start.length && j < end.length;) {
			if(start[i] <= end[j]) {
				++count_wf;
				++i;
				if(max_wf < count_wf) {
					max_wf = count_wf;
				}
			}
			else {
				--count_wf;
				++j;
			}
		}
		
		return max_wf;
	}
}
