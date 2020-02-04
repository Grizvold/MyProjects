package il.co.ilrd.design_pattern.observer;

public class ObserverTest {

	public static void main(String[] args) {
		Subject subject = new Subject();
		
		new Dog(subject);
		new Cat(subject);
		new Chicken(subject);
		
		System.out.println("before change");
		subject.setState(10);
		System.out.println("\n" + "second change");
		subject.setState(20);
	}
}
