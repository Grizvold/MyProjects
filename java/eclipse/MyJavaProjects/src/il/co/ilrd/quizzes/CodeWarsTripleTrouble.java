package il.co.ilrd.quizzes;

public class CodeWarsTripleTrouble {

	public static void main(String[] args) {
		System.out.println(TripleDouble(666789L, 12345667L));
		System.out.println(TripleDouble(451999277L, 41177722899L));
		System.out.println(TripleDouble(1112L, 122L));
		System.out.println(TripleDouble(451999277L, 411777228L));
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
	
//	public static int swap(int x, int y) {
//		return x;
//	}
//	
	public static int TripleDouble(long num1, long num2) {
		String num1_str = String.valueOf(num1);
		String num2_str = String.valueOf(num2);

		for (int i = 0; i < 10; ++i) {
			String n = String.valueOf(i);
			if(num1_str.contains(n +n +n ) && num2_str.contains(n+n)) {
				return 1;
			}
		}
		
		return 0;
	}
}
