package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class QuizzOddEvenIndexes {

	public static void main(String[] args) {
		System.out.println(Arrays.toString(setOddInOddIndexesEvenInEvenIndexes(new int[] {1, 2, 4, 5, 7, 6})));
		System.out.println(Arrays.toString(setOddInOddIndexesEvenInEvenIndexes(new int[] {1, 5, 7, 6})));
		System.out.println(Arrays.toString(setOddInOddIndexesEvenInEvenIndexes(new int[] {1, 2, 4, 6})));
	}

	public static int[] setOddInOddIndexesEvenInEvenIndexes(int[] userArr) {
		List<Integer> oddList = new LinkedList<>();
		List<Integer> evenList = new LinkedList<>();
		int size = 0;
		
		for (int i = 0; i < userArr.length; ++i) {
			if((userArr[i] % 2 == 0)) {
				evenList.add(userArr[i]);
			}
			else {
				oddList.add(userArr[i]);
			}
		}
		
		size = oddList.size() > evenList.size() ? oddList.size() * 2 : evenList.size() * 2;
		int[] resultArr = new int[size];
		for (int i = 0; i < resultArr.length; ++i) {
			if((i % 2) != 0) {
				resultArr[i] = oddList.isEmpty() ? -1 : oddList.remove(0);
			}
			else {
				resultArr[i] = evenList.isEmpty() ? 0 : evenList.remove(0);
			}
		}
		
		return resultArr;
	}
}
