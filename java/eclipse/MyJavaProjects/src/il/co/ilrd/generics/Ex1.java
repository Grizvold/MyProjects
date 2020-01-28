package il.co.ilrd.generics;

import java.util.ArrayList;
import java.util.List;

public class Ex1 {
	
	static <E> void printArray(List<E> array) {
		for(E e : array) {
			System.out.println(e);
		}
		System.out.println("\n");
	}

	public static void main(String[] args) {
		List<String> strArray = new ArrayList<>();
		List<Integer> intArray = new ArrayList<>();
		List<Double> doubleArray = new ArrayList<>();

		for (int i = 0; i < 10; ++i) {
			strArray.add("i = " + i);
			intArray.add(i);
			doubleArray.add(i * 1.5);
		}
		
		printArray(strArray);
		printArray(intArray);
		printArray(doubleArray);
		
		FooReference<String> strReference = new FooReference<>();
		FooReference<Integer> intReference = new FooReference<>();
		FooReference<Double> doubleReference = new FooReference<>();
		
		strReference.setValue("first Value");
		System.out.println(strReference.toString());
		intReference.setValue(2);
		System.out.println(intReference.toString());
		doubleReference.setValue(15.5);
		System.out.println(doubleReference.toString() + "\n");
		
		System.out.println(strReference.getClass());
		System.out.println(intReference.getClass());
		System.out.println(doubleReference.getClass());
	}

}

class FooReference <T>{
	private T t;
	
	public T getValue() {
		return t;
	}
	
	public void setValue(T value) {
		t = value;
	}
	
	@Override
	public String toString() {
		return "Current value: " + t;
	}
}
