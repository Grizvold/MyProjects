package il.co.ilrd.quizzes;

public class QuizzReverseRemoveFibonacci {

	public static void main(String[] args) {
		System.out.println(String.format("fibonacci_alliteratively test:\n%d %d %d %d %d %d %d\n", 
				fibonacci_alliteratively(0), 
				fibonacci_alliteratively(1),
				fibonacci_alliteratively(2),
				fibonacci_alliteratively(3),
				fibonacci_alliteratively(4),
				fibonacci_alliteratively(5),
				fibonacci_alliteratively(8)));
		
		System.out.println(String.format("fibonacci_recursively test:\n%d %d %d %d %d %d %d\n", 
				fibonacci_recursively(0), 
				fibonacci_recursively(1),
				fibonacci_recursively(2),
				fibonacci_recursively(3),
				fibonacci_recursively(4),
				fibonacci_recursively(5),
				fibonacci_recursively(8)));
		
		System.out.println(String.format("fibonacci_dynamic test:\n%d %d %d %d %d %d %d\n", 
				fibonacci_dynamic(0), 
				fibonacci_dynamic(1),
				fibonacci_dynamic(2),
				fibonacci_dynamic(3),
				fibonacci_dynamic(4),
				fibonacci_dynamic(5),
				fibonacci_dynamic(8)));
		
		System.out.println(String.format("Item removal from arr test:\n"
				+ "1, 2, 5, 12, 5, 3, 8 removing 5: %d\n"
				+ "1, 2, 5, 12, 5, 3, 8 removing 1: %d\n"
				+ "1, 1, 1, 1, 1 removing 1: %d\n"
				+ "1, 2, 5, 12, 5, 3, 8 revoming 8: %d\n", 
				removeItemFromArr(new int[] {1, 2, 5, 12, 5, 3, 8}, 5),
				removeItemFromArr(new int[] {1, 2, 5, 12, 5, 3, 8}, 1),
				removeItemFromArr(new int[] {1, 1, 1, 1, 1}, 1),
				removeItemFromArr(new int[] {1, 2, 5, 12, 5, 3, 8}, 8)));
		
		System.out.println(String.format("Reverse number test:\n" + 
				"1234 : %d\n" + 
				"0000 : %d\n" +
				"1000 : %d\n" +
				"0001 : %d\n",
				reverseNumber(1234),
				reverseNumber(0000),
				reverseNumber(1000),
				reverseNumber(0001)));
		
		System.out.println(String.format("Encoding string test:\n" + 
				"aaabbacccc -> %s\n" + 
				" -> %s\n" + 
				"aaabbadc -> %s\n",
				encodeString("aaabbacccc"),
				encodeString(""),
				encodeString("aaabbadc")));
	}
	
	public static int fibonacci_alliteratively(int n) {
		int num_1 = 1;
		int num_2 = 1;
		int num_3 = 0;
		
		if(n == 0) {
			return 0;
		}
		else if (n == 1 || n == 2) {
			return 1;
		}
		
		for (int i = 2; i < n; ++i) {
			num_3 = num_1 + num_2;
			num_1 = num_2;
			num_2 = num_3;
		}
		
		return num_3;
	}

	public static int fibonacci_recursively(int n) {
		if(n == 0) {
			return 0;
		}
		else if (n == 1 || n == 2) {
			return 1;
		}
		
		return fibonacci_recursively(n - 1) + fibonacci_recursively(n- 2); 
	}
	
	public static int fibonacci_dynamic(int n) {
		//the idea is to store values calculated so far in array
		int[] fibonacci_arr = new int[n + 2];
		fibonacci_arr[0] = 0;
		fibonacci_arr[1] = 1;
		
		if(n == 0) {
			return fibonacci_arr[0];
		}
		else if (n == 1 || n == 2) {
			return fibonacci_arr[1];
		}
		
		for (int i = 2; i <= n; ++i) {
			fibonacci_arr[i] = fibonacci_arr[i - 1] + fibonacci_arr[i - 2];
		}
		
		return fibonacci_arr[n];
	}
	
	public static int removeItemFromArr(int[] user_arr, int item) {
		int arr_lenght = user_arr.length;
		
		for (int i = 0; i < user_arr.length; ++i) {
			if(user_arr[i] == item) {
				for (int j = i; j < user_arr.length - 1; ++j) {
					user_arr[j] = user_arr[j + 1];
					user_arr[j + 1] = 0;
				}
				--arr_lenght;
			}
		}
		
		//System.out.println(Arrays.toString(user_arr));
		return arr_lenght;
	}
	
	public static int reverseNumber(int n) {
		int result = 0;
		
		for (; n > 0; n /= 10) {
			result = (result * 10) + n % 10; 
		}
		
		return result;
	}
	
	public static String encodeString(String userString) {
		int stringLenght = userString.length();
		int count = 0;
		String resultString = "";
		
		for (int i = 0; i < stringLenght; ++i) {
			resultString += userString.charAt(i);
			count = 1;
			for (;i < stringLenght - 1 && userString.charAt(i) == userString.charAt(i + 1);) {
				++count;
				++i;
			}
			resultString += count;
		}
		
		return resultString;
	}
}
