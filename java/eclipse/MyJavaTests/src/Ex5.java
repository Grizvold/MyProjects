public class Ex5 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SomeClass sc = new SomeClass();
		sc.foo();
		
		System.out.println(SomeClass.bar());
	}

}


interface SomeInterface{
	default void foo() {
		System.out.println("my foo");
	}
}

class SomeClass implements SomeInterface{
	public void foo() {
		System.out.println("new foo");
	}
	 
	static int x = 5;
	
	static int bar() {
//		final int x = 10;
		
		return --SomeClass.x;
	}
}