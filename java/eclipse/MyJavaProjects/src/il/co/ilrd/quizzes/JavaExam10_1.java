package il.co.ilrd.quizzes;

abstract class Base{
	public Base() {
		System.out.println("In Base");
		foo();
	}
	
	public void foo() {
		System.out.println("Need to implement by " + getName());
	}
	
	abstract public String getName();
}

public class JavaExam10_1 extends Base{
	String ds1;
	int x;
	
	public JavaExam10_1() {
		this.ds1 = "Derived";
		System.out.println("In Derived");
	}
	
	public void foo() {
		System.out.println("In override 'foo' " + ds1);
	}
	

	@Override
	public String getName() {
		return this.ds1;
	}

	@SuppressWarnings("unused")
	public static void main(String[] args) {
		Base ab = new JavaExam10_1();
	}
}
