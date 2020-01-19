package il.co.ilrd.data_structure_exam;

import java.util.regex.Pattern;

public class Ex8a 
{

	static String reverseWords(String str)
	{
		String resultString = "";
		Pattern pattern = Pattern.compile("\\s");
		String[] strArr = pattern.split(str);
		
		for (int i = 0; i < strArr.length; ++i) 
		{
			if(i == strArr.length - 1)
			{
				resultString = strArr[i] + resultString;
			}
			else
			{
				resultString = " " + strArr[i] + resultString;
			}
		}
		
		return resultString;
	}
	
	public static void main(String[] args) 
	{
		System.out.println(reverseWords("Hello there stranger"));
	}

}
