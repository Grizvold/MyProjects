package il.co.ilrd.generics;

import java.util.ArrayList;
import java.util.List;

public class Question25 {

	public static void main(String[] args) {
		List rawList;
		List<?> listOfAnyType;
		List<Object> listOfObject = new ArrayList<Object>();
		List<String> listOfString = new ArrayList<String>();
		List<Integer> listOfInteger = new ArrayList<Integer>();
		
		rawList = listOfString;
		rawList = listOfInteger;
		listOfAnyType = listOfString;
		rawList = listOfAnyType;
		listOfAnyType = listOfInteger;
		//listOfObject =(List<Object>) listOfString;
		
	}

}
