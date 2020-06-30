package il.co.ilrd.quizzes;

public class QuizzInheritancePlay {
	
	protected int x;
	protected int y;
	
	public QuizzInheritancePlay(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	protected void printY() {
		System.out.println("Class A print Y: " + y);
	}
	
	protected void printX() {
		System.out.println("Class A print X: " + x);
	}
	
	protected void f(int z) {
		x += z;
		z = x;
	}
	
	public String toString() {
		return "I'm A";
	}

	public static void main(String[] args) {
		QuizzInheritancePlay A = new QuizzInheritancePlay(1, 5);
		B b1 = A.new C(1, 7);
		int z = 6;
		b1.f(z);
		System.out.println("Z = " + z);
		
		B b2 = A.new B(11, 17);
		QuizzInheritancePlay A2 = b1;
		System.out.println(b1.toString());
		System.out.println(A2.toString());
		System.out.println(b2.toString());
		A2.printX();
		b2.printX();
		A2.printY();
		b2.printY();
	}
	
	class B extends QuizzInheritancePlay{
		public B(int x, int y) {
			super(x, y);
		}
		
		int j;
		
		protected void printY() {
			System.out.println("Class B print Y: " + y);
		}
		
		public String toString() {
			return "I'm B and " + super.toString();
		}
	}

	class C extends B{
		public C(int x, int y) {
			super(x, y);
		}
		
		protected void printX() {
			System.out.println("Class C print x : " + x);
		}
	}
	
}
