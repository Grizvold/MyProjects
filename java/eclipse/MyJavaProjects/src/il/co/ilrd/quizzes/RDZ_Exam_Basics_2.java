package il.co.ilrd.quizzes;

public class RDZ_Exam_Basics_2 {

	public static void main(String[] args) {
		System.out.println((int)reverseBitsInChar((char)1));
		System.out.println((int)reverseBitsInChar((char)128));
		System.out.println((int)reverseBitsInChar((char)7));
	}

	public static char reverseBitsInChar(char input) {
		char reversedNum = 0;
		
		for(int i = 0; i < 8; i++)
	    {
			reversedNum <<= 1;
			reversedNum |= input & 1;
			input >>= 1;
	    }
		
		return reversedNum;
	}
}
