package il.co.ilrd.quizzes;

import java.util.List;
import java.util.ArrayList;

public class QuizzString {
	
	public static void main(String[] args) {
		System.out.println(findSubstirng("ruslanandlan", "lan"));
		System.out.println(reverseString("testString"));
	}
	
	static public List<Integer> findSubstirng(String text, String requestedString)
	{
		List<Integer> indexList = new ArrayList<Integer>();
		
		for (int i = -1; (i = text.indexOf(requestedString, i + 1)) != -1; i++) {
			indexList.add(i);
		}
		
		return indexList;
	}
	
	static public String reverseString(String originalString) {
		String reverseString = "";
		
		for (int i = originalString.length()- 1; i >= 0; --i) {
			reverseString = reverseString + originalString.charAt(i);
		}
		
		return reverseString;
	}

	/*public static void main(String[] args) {
		String subString = "abn";
		System.out.println(strStr(subString));
		StringBuffer testStringBuffer = new StringBuffer("doron");
		System.out.println(reverseString(testStringBuffer));
	}

	static public int strStr(String subString) {
		//String str = new String(this.toString());
		String str = "ruslanlalabn";
		int startSub = 0;
		int chechIndex;
		int j = 0;
		
		for (int i = 0; i < str.length(); ++i) {
			startSub = i;
			chechIndex = i;
			for (j = 0; j < subString.length(); ++j) {
				if(str.charAt(chechIndex) != subString.charAt(j)) {
					break;
				}
				++chechIndex;
			}
			if(j == subString.length()) {
				break;
			}
			startSub = -1;
		}
		
		return startSub;
	}*/
	
	static public String reverseString(StringBuffer str) {
		//StringBuffer stringBuffer = new StringBuffer(this.);
		for (int i = 0; i < str.length()/2; ++i) {
			int len = str.length();
			char c = str.charAt(i);
			
			str.setCharAt(i,  str.charAt(len - 1 -i));
			str.setCharAt(len - 1 - i, c);
		}
		
		return str.toString();
	}
}
