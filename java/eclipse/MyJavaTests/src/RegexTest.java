import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexTest {

	public static void main(String[] args) {
		StringBuilder stringBuilder = new StringBuilder("[5,10,[2,3,[1,1,]][1,1,][2,3,[1,5,]]]");
		
		System.out.println("before " + stringBuilder);
		String regex_1 = "(\\,\\[)";
		Pattern pattern = Pattern.compile(regex_1, Pattern.CASE_INSENSITIVE);
		Matcher matcher = pattern.matcher(stringBuilder.toString());
		
		stringBuilder = new StringBuilder(matcher.replaceAll(" [")); 
		
		String regex_2 = "\\,\\]";
		pattern = Pattern.compile(regex_2, Pattern.CASE_INSENSITIVE);
		matcher = pattern.matcher(stringBuilder.toString());
		stringBuilder = new StringBuilder(matcher.replaceAll("]")); 
		System.out.println("after " + stringBuilder);
	}

}
