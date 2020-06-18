package il.co.ilrd.quizzes;

public class CodeWarsBreakcamelCase {

	public static void main(String[] args) {
		System.out.println(camelCase("camelString"));
		System.out.println(camelCase(" WhatIf Like thiS") + "\n");
		
		System.out.println(fastCamelCase("camelString"));
		System.out.println(fastCamelCase(" WhatIf Like thiS"));
	}

	public static String camelCase(String input) {
		String result="";
		
		for (int i = 0; i < input.length(); ++i) {
			if(Character.isUpperCase(input.charAt(i))) {
				result+=" ";
			}
			result+=input.charAt(i);
		}
		
		return result.trim();
	}
	
	public static String fastCamelCase(String input) {
		return input.replaceAll("([A-Z])", " $1").trim();
	}
}
