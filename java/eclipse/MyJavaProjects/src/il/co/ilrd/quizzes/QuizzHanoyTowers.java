package il.co.ilrd.quizzes;

public class QuizzHanoyTowers {

	public static void main(String[] args) {
		hanoyTower(2, 'A', 'B', 'C');
	}

	public static void hanoyTower(int n, char from, char aux, char to) {
		if(n == 1) {
			System.out.println("move disk 1 from " + from + " to " + to);
			return;
		}
		
		hanoyTower(n - 1, from, to, aux);
		System.out.println("move disk " + n + " from " + from + " to " + to);
		hanoyTower(n - 1, aux, from, to);
	}
}
