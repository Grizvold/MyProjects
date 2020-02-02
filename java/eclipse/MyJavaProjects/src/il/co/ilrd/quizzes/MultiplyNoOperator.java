package il.co.ilrd.quizzes;

public class MultiplyNoOperator {

	public static int multiply(int x, int y) {
		if (y == 1)
		{
			return x;
		}
		
		return x + multiply(x, --y);
	}
	
	public static void main(String[] args) {
		System.out.println(multiply(2, 3));
	}

}
