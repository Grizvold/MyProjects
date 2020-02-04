package il.co.ilrd.design_pattern.observer;

public abstract class Observer {
	protected Subject subject;
	public abstract void update();
}

class Dog extends Observer{
	
	public Dog(Subject subject) {
		this.subject = subject;
		this.subject.addObserver(this);
	}
	
	@Override
	public void update() {
		System.out.println("Dog observer: " + subject.getState());
	}
}

class Cat extends Observer{

	public Cat(Subject subject) {
		this.subject = subject;
		this.subject.addObserver(this);
	}
	
	@Override
	public void update() {
		System.out.println("Cat observer: " + subject.getState());
	}
}

class Chicken extends Observer{

	public Chicken(Subject subject) {
		this.subject = subject;
		this.subject.addObserver(this);
	}
	
	@Override
	public void update() {
		System.out.println("Chicken observer: " + subject.getState());
	}
}