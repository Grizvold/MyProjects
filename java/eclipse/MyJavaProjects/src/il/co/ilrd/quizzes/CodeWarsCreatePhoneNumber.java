package il.co.ilrd.quizzes;

public class CodeWarsCreatePhoneNumber {

	public static void main(String[] args) {
		System.out.println(createPhoneNumber(new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}));
		
		System.out.println(short_createPhoneNumer(new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}));
	}
	
	public static String createPhoneNumber(int[] numbers) {
		String area = "";
		String second_three = "";
		String the_rest = "";
		for (int i = 0; i < numbers.length; ++i) {
			if(i < 3) {
				area += numbers[i];
			}
			else if (i > 2 && i < 6) {
				second_three += numbers[i];
			}
			else {
				the_rest += numbers[i];
			}
		}
		return "(" + area + ")" + " " + second_three + "-" + the_rest;
	}
	
	public static String short_createPhoneNumer(int[] numbers) {
		return String.format("(%d%d%d) %d%d%d-%d%d%d%d", 
				numbers[0],numbers[1],numbers[2],
				numbers[3],numbers[4],numbers[5],
				numbers[6],numbers[7],numbers[8],numbers[9]);
	}

}
