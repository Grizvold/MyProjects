package il.co.ilrd.quizzes;

public class CodeWarsSquareNumber {
	
	public static void main(String[] args) {
		System.out.println(isSquare(1));
		System.out.println(isSquare(3));
		System.out.println(isSquare(2));
		System.out.println(isSquare(4));
		System.out.println(isSquare(16));
		System.out.println(isSquare(24));
	}
	
	  public static boolean isSquare(int n) {
		  return Math.sqrt(n) % 1.0 == 0;
	  }
}


