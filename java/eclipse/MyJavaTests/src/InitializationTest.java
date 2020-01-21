public class InitializationTest {
 
	//instance variable initializer
	String s = "abc";
	private int x;
	private int y;
	private int z;
 
	//constructor
	public InitializationTest() 
	{
		this.z = y + 1;
		this.x = 1;
		this.y = x + 1;
		System.out.println("constructor called");
	}
 
	{
		System.out.println("instance initializer 3 called");
	}
	
	//static initializer
	static 
	{
		System.out.println("static initializer called");
	}
 
	//instance initializer
	{
		System.out.println("instance initializer called");
	}
	
	{
		System.out.println("instance initializer 2 called");
	}
 
	static 
	{
		System.out.println("static initializer 2 called");
	}
 
	public static void main(String[] args) {
//		InitializationTest a = new InitializationTest();
//		System.out.println(a.x);
//		System.out.println(a.y);
//		System.out.println(a.z);
//		
//		int[] intArr = new int[5];
//		System.out.println(intArr.length);
		//new InitializationTest();
		
		ChildOfInitializer random = new ChildOfInitializer();
		
	}
}

class ChildOfInitializer extends InitializationTest
{
	static
	{
		System.out.println("child static block");
	}
	
	{
		System.out.println("child non static block");
	}
	
	public ChildOfInitializer()
	{
		super();
		System.out.println("child ctor");
	}
}