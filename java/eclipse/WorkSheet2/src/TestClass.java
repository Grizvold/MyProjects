/**
 * 
 */

/**
 * @author student
 *
 */

class Parent{
	int x = 5;
	
	public void printTest() {
		int x = 4;
		System.out.println(x);
	}
}

class Child extends Parent{
	int x = 4;
	public void printTest() {
		System.out.println(x);
	}
}

public class TestClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

	//Parent parent = new Child();	
	Child testChild = new Child();
	testChild.printTest();
	}

}
