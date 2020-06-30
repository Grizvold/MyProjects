package il.co.ilrd.quizzes;

public class CodeWarsHighestScoringWord {

	public static void main(String[] args) {
		System.out.println(high("man i need a taxi up to ubud"));
		System.out.println(high("what time are we climbing up to the volcano"));
		System.out.println(high("take me to semynak"));
		System.out.println(high(" qkottecoj fjzuwug "));
	}

	public static String high(String s) {
		String[] words = s.toLowerCase().trim().split(" ");
		int[] words_value_Array = new int[words.length];
		int word_counter = 0;
		
		for (String current_word : words) {
			int word_score = 0;
			for (int i = 0; i < current_word.length(); ++i) {
				word_score += current_word.charAt(i) - 96;
			}
			
			words_value_Array[word_counter] = word_score;
			++word_counter;
		}
		
 		int max_value = 0;
 		int max_index = 0;
 		for (int i = 0; i < words_value_Array.length; ++i) {
			if(max_value < words_value_Array[i]) {
				max_value = words_value_Array[i];
				max_index = i;
			}
		}
 		
		return words[max_index];
	}
}
