import java.util.Arrays;

/**
 * 
 */

/**
 * @author student
 *
 */

enum Level{
	High,
	Medium,
	Low
}

class Parent{
	//int x = 5;
	
	Parent()
	{
		printTest();
	}
	
	public void printTest(){
	//	int x = 4;
		System.out.println("test parent");
	}
}

class Child extends Parent{
	int x = 4;
	public void printTest() {
		System.out.println(x);
	}
}

class Foo {
	public String exerciseString = "exerciseString";
	
	public void foo(short x)
	{
		System.out.println("inside short");
	}
	
	public void foo(long x)
	{
		System.out.println("inside long");
	}
	
	public void foo(Integer x)
	{
		System.out.println("inside Integer");
	}
}

class Foo2 {
	public String exerciseString2 = "exerciseString";
}

public class TestClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		/*int []arr1 = {1,2};
		int []arr2 = {1,2};
		System.out.println(arr1.equals(arr2));
		System.out.println(Arrays.equals(arr1, arr2));*/
		
		String s1 = "hi";
		//String s2 = new String("hi");
		String s3 = "hi";
		
		System.out.println((s1 == s3));
		System.out.println(s1.equals(s3));
		
		Integer i = 1;
		Integer j = 2;
		Integer k = ++i;
		
		int z = 1;
		int x = 1;
		
		System.out.println("primitive type " + (z == x));
		System.out.println("equals privimitive " + ((Integer)x).equals(z));
		
		int[] arr1 = {1,2,3};
		int[] arr2 = {1,2,3}; 
		
		System.out.println("arrays " + (arr1 == arr2));
		System.out.println(arr1.equals(arr2));
		System.out.println(Arrays.equals(arr1, arr2));
		
		System.out.println(j == k);
		System.out.println(k.equals(j));
		
		Child child = new Child();
		child.printTest();
		
		Foo testFoo = new Foo();
		testFoo.foo(10);
		
		/*String text    =
		        "This is the text to be searched " +
		        "for occurrences of the http:// pattern.";

		String regex = ".*tex.*";

		boolean matches = Pattern.matches(regex, text);

		System.out.println("matches = " + matches);*/
		Boolean boolean1 = true;
		System.out.println(boolean1? true:false);
		
		String str = new String("exerciseString");
		
		Foo exerciseTest1 = new Foo();
		Foo2 exerciseTestFoo2 = new Foo2();
		System.out.println(exerciseTest1.exerciseString + " " + exerciseTestFoo2.exerciseString2);
		System.out.println(exerciseTest1.exerciseString == exerciseTestFoo2.exerciseString2);
		System.out.println(exerciseTest1.exerciseString == str);
		
		Level enumtestLevel = Level.High;
		enumtestLevel = Level.Low;
		System.out.println(enumtestLevel);
	}

}
