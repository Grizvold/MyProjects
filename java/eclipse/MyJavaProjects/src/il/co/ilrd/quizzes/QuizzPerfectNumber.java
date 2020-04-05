package il.co.ilrd.quizzes;

public class QuizzPerfectNumber {

	public static void main(String[] args) {
		System.out.println("result of 1 is: " + perfectNumber(1) + "\n");
		System.out.println("result of 2 is: " + perfectNumber(2)+ "\n");
		System.out.println("result of 8 is: " + perfectNumber(8)+ "\n");
		System.out.println("result of 11 is: " + perfectNumber(11)+ "\n");
		System.out.println("result of 28 is: " + perfectNumber(28)+ "\n");
		System.out.println("result of 29 is: " + perfectNumber(29)+ "\n");
	}

	public static int perfectNumber(int userNumber) {
		int digitSum = sumOfDigits(userNumber);
		System.out.println("sum of digits: " + digitSum);
		//check if </=/> to 10
		if(10 > digitSum) {
			userNumber = userNumber * 10 + (10 - userNumber);
			return userNumber;
		}
		else if(10 == digitSum) {
			return userNumber;
		}
		else {
			return perfectNumber(digitSum);
		}
	}
	
	private static int sumOfDigits(int number) {
		int sum;
		for(sum = 0; number > 0; number /= 10) {
			sum += (number % 10);
		}
		return sum;
	}
}
