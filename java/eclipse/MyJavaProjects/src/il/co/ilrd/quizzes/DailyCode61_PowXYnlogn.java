package il.co.ilrd.quizzes;

public class DailyCode61_PowXYnlogn {

	public static void main(String[] args) {
		System.out.println("2 ^ 3 = " + pow(2, 3));
		System.out.println("5 ^ 5 = " + pow(5, 5));
		System.out.println("5 ^ 2 = " + pow(5, 2));
	}
	
	public static int pow(int x, int y) {
		int temp;
		
		if(y == 0) {
			return 1;
		}
		
		temp = pow(x, y / 2);
		
		if(y % 2 == 0) {
			return temp * temp;
		}
		else {
			return x * temp * temp;
		}
	}
}
