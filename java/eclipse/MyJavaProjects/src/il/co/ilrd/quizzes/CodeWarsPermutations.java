package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class CodeWarsPermutations {

	public static void main(String[] args) {
		singlePermutations("abba");

	}
	
	
	public static List<String> singlePermutations(String s) {
        Set<String> result_set = new HashSet<>();
        permutation("", s, result_set);
        List<String> result_list = new ArrayList<String>(result_set);
        
        return result_list;
    }
	
	public static void permutation(String prefix, String str, Set<String> set) {
		int n = str.length();
		if(n == 0) {
			set.add(prefix);
		}
		else {
			for(int i = 0; i < n; i++) {
				permutation(prefix + str.charAt(i), str.substring(0, i) + str.substring(i + 1, n), set);
			}
		}
	}
}
