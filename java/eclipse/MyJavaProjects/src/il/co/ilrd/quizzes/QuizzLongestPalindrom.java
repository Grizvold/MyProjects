package il.co.ilrd.quizzes;

public class QuizzLongestPalindrom {

	public static void main(String[] args) {
		System.out.println(longest_Polindrom("tesed"));
	}

	public static String longest_Polindrom(String userString) {
		String polindrom = "";
		
		for (int i = 0; i < userString.length(); i++) {
			for (int j = userString.length() - 1; j > i; --j) {
				if (userString.charAt(i) == userString.charAt(j)) {
				 	if(potentialPolindromSize(userString.substring(i, j + 1)) > polindrom.length()) {
				 		polindrom = userString.substring(i, j + 1);
				 	}
				}
			}
		}
		
		return polindrom;
	}

	private static int potentialPolindromSize(String testString) {
		int start = 0, end = testString.length() - 1;
		int polindromSize = 0;
		
		while (start < end) {
			if(testString.charAt(start) == testString.charAt(end)) {
				polindromSize += 2;
				++start; 
				--end;
			}
			else {
				polindromSize = 0;
				return polindromSize;
			}
		}
		
		return testString.length() % 2 == 0 ? polindromSize : polindromSize + 1;
	}
}
