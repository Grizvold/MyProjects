package il.co.ilrd.data_structure_exam;

import java.util.Arrays;

public class Ex1a {
	
	private int[] intArray;
	
	Ex1a(int sizeOfArray) {
		intArray = new int[sizeOfArray];
	}
	
	public void setVal(int index, int value) {
		intArray[index] = value;
	}
	
	public int getVal(int index) {
		return intArray[index];
	}

	public static void main(String[] args) {
		Ex1a ex1a = new Ex1a(10);
		int valueInArr[] = new int[10];
		System.out.println(ex1a.getVal(0));
		System.out.println(valueInArr.length);
	}
}
