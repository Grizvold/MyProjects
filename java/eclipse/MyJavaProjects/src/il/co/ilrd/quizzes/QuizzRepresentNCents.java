package il.co.ilrd.quizzes;

public class QuizzRepresentNCents {

	public static void main(String[] args) {
		System.out.println(String.format("num of ways to represent numberOfWays_iterative:\n" 
				+ "1 -> %d\n"
				+ "5 -> %d\n"
				+ "10 -> %d\n"
				+ "25 -> %d\n"
				+ "6 -> %d\n"
				+ "11 -> %d\n"
				+ "41 -> %d\n",
				numberOfWays_iterative(1),
				numberOfWays_iterative(5),
				numberOfWays_iterative(10),
				numberOfWays_iterative(25),
				numberOfWays_iterative(6),
				numberOfWays_iterative(11),
				numberOfWays_iterative(41)));

		System.out.println(String.format("num of ways to represent numberOfWays_recursively:\n" 
				+ "1 -> %d\n"
				+ "5 -> %d\n"
				+ "10 -> %d\n"
				+ "25 -> %d\n"
				+ "6 -> %d\n"
				+ "11 -> %d\n"
				+ "41 -> %d\n",
				numberOfWays_recursively(1, 25),
				numberOfWays_recursively(5, 25),
				numberOfWays_recursively(10, 25),
				numberOfWays_recursively(25, 25),
				numberOfWays_recursively(6, 25),
				numberOfWays_recursively(11, 25),
				numberOfWays_recursively(41, 25)));
	}

	public static int numberOfWays_iterative(int num_of_cents) {

        int[] coins_arr = new int[] {1, 5, 10, 25};
        int[] representation_arr = new int[num_of_cents + 1]; //longest option = only cents
        representation_arr[0] = 1;

        for (int i = 0; i < coins_arr.length; ++i) {
            for (int j = 1; j <= num_of_cents; ++j) {
                if (j >= coins_arr[i]) {
                    representation_arr[j] = representation_arr[j] + representation_arr[j - coins_arr[i]];
                }
            }
        }
        
        return representation_arr[num_of_cents];
    }
	
	public static int numberOfWays_recursively(int num_of_cents, int representation) {
	    int next_representation = 0;
	    switch (representation) {
	    case 25:
	    	next_representation = 10;
	        break;
	    case 10:
	    	next_representation = 5;
	        break;
	    case 5:
	    	next_representation = 1;
	        break;
	    case 1:
	        return 1;
	    }
	    
	    int ways = 0;
	    for (int i = 0; i * representation <= num_of_cents; i++) {
	        ways += numberOfWays_recursively(num_of_cents - i * representation, next_representation);
	    }
	    
	    return ways;
	}
}
