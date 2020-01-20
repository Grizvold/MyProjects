package il.co.ilrd.reflection;

public class AnalizedClass extends AnotherClass implements InterfaceOne, InterfaceTwo 
{
	
	private int x = 1;
	private int y = 2;
	public int z = 3;
	
	public AnalizedClass()
	{
	}
	
	public AnalizedClass(int x, int y, int z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public void setX(int x)
	{
		this.x = x;
	}
	
	public void setY(int y)
	{
		this.y = y;
	}
	
	public int getX()
	{
		return x;
	}
	
	public int getY()
	{
		return y;
	}
	
	public void firstFunc() 
	{
		System.out.println("first iterface and first func");
	}
	
	public void secondFunc() 
	{
		System.out.println("second interface and second func");
	}
	
	public void classFunc() 
	{
		System.out.println(intTwo);
	}
	
	@Override
	public void parentFoo()
	{
		System.out.println("parent first overriden foo");
	}
}


class AnotherClass
{
	public void parentFoo()
	{
		System.err.println("parent first foo");
	}
	
	public void parentSecondFoo()
	{
		System.out.println("parent second foo");
	}
}