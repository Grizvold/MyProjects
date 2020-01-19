package il.co.ilrd.data_structure_exam;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Ex5b 
{

	static List<String> listOfAnagrams = new ArrayList<>();
	
	static int hashFunc(String strValue)
	{
		int i = 0;
		strValue = sortInputString(strValue);
		
		for (String str : listOfAnagrams) 
		{
			if(str.equals(strValue))
			{
				return i;
			}
				++i;
		}
		
		listOfAnagrams.add(strValue);
		return i;
	}
	
	private static String sortInputString(String str)
	{
		char[] charArr = str.toCharArray();
		Arrays.sort(charArr);
		
		return new String(charArr);
	}
	
	public static void main(String[] args) 
	{
		System.out.println(hashFunc("test"));
		System.out.println(hashFunc("ttes"));
		System.out.println(hashFunc("sett"));
		System.out.println(hashFunc("ruslan"));
		
	}

}
