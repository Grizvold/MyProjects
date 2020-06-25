package il.co.ilrd.quizzes;

public class CodeWarsTripleTrouble {

	public static void main(String[] args) {
		System.out.println(TripleDouble(666789L, 12345667L));
		System.out.println(TripleDouble(451999277L, 41177722899L));
//		
//		System.out.println(checkForDuplicaitons("bannanas", 'n', 1));
		
//		int a = 10;
//		int b = 20;
//		
//		
//		System.out.println("before: " + "value of a: " + a + " " + "value of b:"  + b);
//		a = swap(b, b = a);
//		System.out.println("after: " + "value of a: " + a + " " + "value of b:"  + b);
	}
	
	public static int swap(int x, int y) {
		return x;
	}
	
	public static int TripleDouble(long num1, long num2) {
		String num1_str = Long.toString(num1);
		String num2_str = Long.toString(num2);

		char triple_char = checkForTriple(num1_str);
		if(checkForTriple(num1_str) == '\0') {
			return 0;
		}
		return checkForDouble(num2_str, triple_char);
	}
	
	private static char checkForTriple(String num_str) {
		int counter = 1;
		
		for (int i = 1; i < num_str.length(); ++i) {
			counter = 1;
			while(num_str.charAt(i) == num_str.charAt(i - 1)) {
				++counter;
				++i;
				if(counter == 3) {
					return num_str.charAt(i);
				}
			}
		}
		
		return '\0';
	}
	
	private static int checkForDouble(String num_str, char triple_char) {
		int result = 0;
		int counter = 1;
		
		if(!num_str.contains(Character.toString(triple_char))) {
			return 0;
		}
		
		for (int i = 1; i < num_str.length(); ++i) {
			counter = 1;
			while(num_str.charAt(i) == num_str.charAt(i - 1)) {
				++counter;
				++i;
				if(counter == 2) {
					result = 1;
					return result;
				}
			}
		}
		
		return result;
	}
}
