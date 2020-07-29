package il.co.ilrd.quizzes;

public class CodeWarsDecodeMorseCode {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

	public static String decode(String morseCode) {
	      String result = "";
	      for(String word : morseCode.trim().split("   ")) {
	        for(String letter : word.split("\\s+")) {
//	          result += MorseCode.get(letter);
	        }
	        result += ' ';
	      }
	      return result.trim();
	}
}
