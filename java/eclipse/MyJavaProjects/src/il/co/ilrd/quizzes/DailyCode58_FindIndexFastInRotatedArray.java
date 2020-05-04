package il.co.ilrd.quizzes;

public class DailyCode58_FindIndexFastInRotatedArray {
	
	public static void main(String[] args) {
		
	}
	
	public static int findPivot(int arr[], int lowIndex, int highIndex) {
		
		if(lowIndex > highIndex) {
			return -1;
		}
		if(lowIndex == highIndex) {
			return lowIndex;
		}
		
		return 0;
	}

}
