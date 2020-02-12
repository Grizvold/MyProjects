package il.co.ilrd.quizzes;

public class CodeWarsJadenString {
	public static void main(String[] args) {
		System.out.println(toJadenCase("how Can Mirrors be real if our eyes aren't real"));
	}
	

	public static String toJadenCase(String phrase) {
		char[] phraseChars = phrase.toCharArray();
		
		for (int i = 0; i < phraseChars.length; ++i) {
			if (i == 0 || phraseChars[i - 1] == ' ') {
				phraseChars[i] = Character.toUpperCase(phraseChars[i]);
			}
		}
	
		return String.valueOf(phraseChars);
	}
}
