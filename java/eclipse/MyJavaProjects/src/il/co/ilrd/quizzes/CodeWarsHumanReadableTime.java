package il.co.ilrd.quizzes;

public class CodeWarsHumanReadableTime {

	public static void main(String[] args) {
		System.out.println(makeReadable(3600));
		System.out.println(makeReadable(5));
	}
	
	public static String makeReadable(int seconds) {
		int hrs = 0, mins = 0, secs = 0;
		
		hrs = seconds / 3600;
		mins = (seconds / 60) % 60;
		secs = seconds % 60;
		
		return String.format("%s:%s:%s", 
				String.format("%02d", hrs),
				String.format("%02d", mins),
				String.format("%02d", secs)); 
	}
}
