package il.co.ilrd.quizzes;

public class QuizzHotelManager {

	public static void main(String[] args) {
		System.out.println(hotel_Manager(new int[] {1, 3, 5}, new int[] {2, 6, 10}, 1));
		System.out.println(hotel_Manager(new int[] {1, 3, 5}, new int[] {2, 4, 6}, 1));
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
}
