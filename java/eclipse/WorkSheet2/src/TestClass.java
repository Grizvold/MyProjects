
/**
 * 
 */

/**
 * @author student
 *
 */

class Parent{
	String cityString = "Parent city";
}

class Child extends Parent{
	String cityString = "Child city";
	int i = 5;
}

class RandomClass{
	float u = 8.5f;
}

public class TestClass {

	public static void main(String[] args) {
		Parent xParent = new Child();
		System.out.println(((Child)xParent).cityString);
		System.out.println(((Child)xParent).i);
	}	
}
