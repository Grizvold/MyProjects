package il.co.ilrd.quizzes;

public class QuizzStringRotation {
	public static void main(String[] args) {
		System.out.println("Is 1234 rotation of 3412? " + isRotation("1234", "3412"));
		System.out.println("Is Ruslan rotation of anR? " + isRotation("Ruslan", "anR"));
		System.out.println("Is Doron rotation of onR? " + isRotation("Doron", "onR"));
	}
	
	public static boolean isRotation(String original, String rotation) {
		if(original == null || rotation == null) {
			return false;
		}
		
		if(original.length() != original.length()) {
			return false;
		}
		
		String concatString = original + original;
		return concatString.contains(rotation);
	}
}
