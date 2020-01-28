package il.co.ilrd.generics;

import java.util.ArrayList;
import java.util.List;

public class Question4 {

	public static void main(String[] args) {
		List<String> v = new ArrayList<String>();
		v.add("test");
		String integer = v.get(0);
		System.out.println(integer);
		
		doSomething(v);
		
		List <Object> listOfObjects = new ArrayList<Object>();
		listOfObjects.add("something");
		System.out.println(listOfObjects.get(0));
		
		List <String> listofStrings = new ArrayList<String>();
		listofStrings.add("hey");
		System.out.println(listofStrings.get(0));
		
		//listOfObjects = listofStrings;
	}
	
	static public void doSomething(List<? extends String> stringList){
		System.out.println("doing something");
	}
}
