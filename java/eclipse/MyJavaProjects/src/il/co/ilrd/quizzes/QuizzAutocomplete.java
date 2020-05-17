package il.co.ilrd.quizzes;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class QuizzAutocomplete {

	public static void main(String[] args) {
		Set<String> setOfStrings = new HashSet<>(Arrays.asList(new String[] {"dog", "deer", "deal"}));
		
		//test 1
		System.out.println(Arrays.toString(autocompleteSystem(setOfStrings, "de").toArray()));
		System.out.println(Arrays.toString(autocompleteSystem(setOfStrings, "do").toArray()));
		
		//test 2
		setOfStrings = new HashSet<>(Arrays.asList(new String[] {"amoral", "acellular", "abyss", "achromatic", "anhydrous"}));
		System.out.println(Arrays.toString(autocompleteSystem(setOfStrings, "ac").toArray()));
		System.out.println(Arrays.toString(autocompleteSystem(setOfStrings, "a").toArray()));
		System.out.println(Arrays.toString(autocompleteSystem(setOfStrings, "ab").toArray()));
	}

	public static Set<String> autocompleteSystem(Set<String> setOfStrings, String prefix){
		Set<String> result_set = new HashSet<String>();
		int prefixHash = prefix.hashCode();
		int prefixLenght = prefix.length();
		
		for (String string : setOfStrings) {
			String tempString = string.substring(0, prefixLenght);
			if(tempString.hashCode() == prefixHash) {
				//not enough to check only hash -> need to check strings themselves
				if(tempString.equals(prefix)) {
					result_set.add(string);
				}
			}
		}
		
		return result_set;
	}
}
