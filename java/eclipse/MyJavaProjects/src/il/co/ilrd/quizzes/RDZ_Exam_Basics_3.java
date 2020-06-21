package il.co.ilrd.quizzes;

public class RDZ_Exam_Basics_3 {

	public static void main(String[] args) {
		System.out.println(isPowerOf2(4));
		System.out.println(isPowerOf2(8));
		System.out.println(isPowerOf2(16));
		System.out.println(isPowerOf2(3));
		System.out.println(isPowerOf2(5));
		
	}

	public static boolean isPowerOf2(int input) {
		return (input & (input - 1)) == 0 ? true : false;
	}
}
