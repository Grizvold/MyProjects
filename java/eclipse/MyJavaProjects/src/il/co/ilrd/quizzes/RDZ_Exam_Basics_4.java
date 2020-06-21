package il.co.ilrd.quizzes;

public class RDZ_Exam_Basics_4 {
	public static final int int_size = 32;

	public static void main(String[] args) {
		System.out.println(rotateRight(7, 20));
		System.out.println(rotateRightByBlock(7, 20));
	}

	public static int rotateRight(int input, int numberOfRotations) {
		numberOfRotations %= 32;
		for (int i = 0; i < numberOfRotations; ++i) {
			int temp = 1 & input;
			input = (temp << 31) | (input >>> 1);
		}
		
		return input;
	}
	
	public static int rotateRightByBlock(int input, int numberOfRotations) {
		numberOfRotations %= 32;
		
		return (input >> numberOfRotations) | (input << (int_size - numberOfRotations));
	}
}