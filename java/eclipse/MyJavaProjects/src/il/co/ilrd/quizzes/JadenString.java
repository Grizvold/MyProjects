package il.co.ilrd.quizzes;

public class JadenString {
	public static void main(String[] args) {
		
	}
	

	public static String toJadenCase(String phrase) {
	  // -32 ASCII
		/*Not Jaden-Cased: "How can mirrors be real if our eyes aren't real"
			Jaden-Cased:     "How Can Mirrors Be Real If Our Eyes Aren't Real"*/
	    String arrayOfWords[] = phrase.split(" ");
	    String resultString;
	    String word;
	    char tempChar;
	    for (String string : arrayOfWords) {
			tempChar = string.charAt(0);
			word = string;
			if(tempChar > 96) {
				tempChar -= 32;
//				string 
//				resultString += ; 
			}
		}
			String result;
			return null;
		}
}
