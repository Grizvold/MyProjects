package il.co.ilrd.collection;

import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class CollectionExercises {

	public static void main(String[] args) {
		Integer[] spam1 = new Integer[] { 1, 2, 3, 5};
		Integer[] spam2 = new Integer[] { 1, 2, 3 };
		List<Integer> list = Arrays.asList(spam1);
		
		for (Integer integer : list) {
			System.out.println(integer);
		}
		System.out.println("original " + list);
		Collections.shuffle(list);
		System.out.println("after shuffling " + list);
		list.sort(null);
		System.out.println("after sorting " + list);
		System.out.println(Arrays.toString(spam1));
		Arrays.fill(spam1, 1);
		list = Arrays.asList(spam1);
		System.out.println("after fill " + list);
		System.out.println("binary search " + Arrays.binarySearch(spam1, 1));
		System.out.println("equals " + Arrays.equals(spam1, spam2) + "\n");
		
		
		Map<String, Integer> randomMap = new LinkedHashMap<>();
		randomMap.put("Sunday", 1);
		randomMap.put("Monday", 2);
		randomMap.put("Tuesday", 3);
		randomMap.put("Wednesday", 4);
		randomMap.put("Thursday", 5);
		randomMap.put("Friday", 6);
		randomMap.put("Saturday", 7);
		
		for (Map.Entry<String, Integer> entry : randomMap.entrySet()) {
			System.out.println("key is: " + entry.getKey());
			System.out.println("values are: " + entry.getValue());
		}
		
		System.out.println("\nUsing lamba expression: ");
		randomMap.forEach((key, value)-> System.out.println(key + " = " + value));
	}

}
