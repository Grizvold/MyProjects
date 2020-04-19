package il.co.ilrd.quizzes;

public class DailyCode_NxM_FromTopToBottom {

	public static void main(String[] args) {
		//recursive solution
		System.out.println("Recursive Solutions:");
		System.out.println(recursiveSolution(1, 1));
		System.out.println(recursiveSolution(2, 2));
		System.out.println(recursiveSolution(3, 3));
		System.out.println(recursiveSolution(4, 4));
		System.out.println(recursiveSolution(5, 5));
		
		//dynamic solution 
		System.out.println("\nDynamic Solutions:");
		System.out.println(dynamicSolution(1, 1));
		System.out.println(dynamicSolution(2, 2));
		System.out.println(dynamicSolution(3, 3));
		System.out.println(dynamicSolution(4, 4));
		System.out.println(dynamicSolution(5, 5));
	}

	
	public static int recursiveSolution(int n, int m) {
		//if column or row == 1
		if(n == 1 || m == 1) {
			return 1;
		}
		
		return recursiveSolution(n - 1, m) + 
				recursiveSolution(n, m - 1);
	}
	
	public static int dynamicSolution(int n, int m) {
		int[][] helper_arr = new int[n][m];
		
		for (int i = 0; i < n; i++) {
			helper_arr[i][0] = 1;
		}
		
		for (int i = 0; i < m; i++) {
			helper_arr[0][i] = 1;
		}
		
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				helper_arr[i][j] = helper_arr[i - 1][j] + helper_arr[i][j - 1];
			}
		}
		
		return helper_arr[n -1][m -1];
	}
}
