package il.co.ilrd.quizzes;

public class RDZ_Exam_Basics_1 {

	public static void main(String[] args) {
		System.out.println(countBits((char)15));
		System.out.println(countBits((char)8));
		System.out.println(countBits((char)12) + "\n");
		
		System.out.println(fast_countBits((char)15));
		System.out.println(fast_countBits((char)8));
		System.out.println(fast_countBits((char)12));
	}

	
	public static int countBits(char input) {
		int count = 0; 
		while (input > 0) { 
			count += input & 1; 
			input >>= 1; 
		} 
		return count; 
	}
	
	public static int fast_countBits(int input) {
//		if(input == 0) {
//			return 0;
//		}
//		
//		else {
//			return 1 + fast_countBits(input & (input - 1));
//		}
		
		int count = 1;
		input = input & (input - 1);
		while(input > 0){
			++count;
			input &= (input - 1);
		}
		
		return count;
	}
}
