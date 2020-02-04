package il.co.ilrd.my_tests;

import java.util.ArrayList;
import il.co.ilrd.design_pattern.FactoryPattern;

public class FactoryTest {

	public static void main(String[] args) {
		ArrayList<Object> dogArgs = new ArrayList<Object>();
		ArrayList<Object> catArgs = new ArrayList<Object>();
		ArrayList<Object> chickenArgs = new ArrayList<Object>();
		FactoryPattern<Animal, String, ArrayList<Object>> factory = new FactoryPattern<>();
		
		dogArgs.add(0, 4);
		dogArgs.add(1, "Rexi");
		catArgs.add(0, 4);
		catArgs.add(1, "Yuki");
		chickenArgs.add(0, 2);
		chickenArgs.add(1, "Kuki");
		
		factory.add("Dog", (arguments)->new Dog(dogArgs));
		factory.add("Cat", (arguments)->new Cat(catArgs));
		factory.add("Chicken", (arguments)->new Chicken(chickenArgs));
		
		Animal dog = factory.create("Dog", dogArgs);
		Animal cat = factory.create("Cat", catArgs);
		Animal chicken = factory.create("Chicken", chickenArgs);
		
		dog.makeSound();
		cat.makeSound();
		chicken.makeSound();
	}

}

interface Animal{
	public void makeSound();
	public String getName();
	public int getNumberOfLegs();
}

class Dog implements Animal{
	private int numOfLegs;
	private String name;
	
	public Dog(ArrayList<Object> args) {
		numOfLegs = (Integer)args.get(0);
		name = (String)args.get(1);
	}
	
	@Override
	public void makeSound() {
		System.out.println("hav hav");
		
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public int getNumberOfLegs() {
		return numOfLegs;
	}
}

class Cat implements Animal{
	private int numOfLegs;
	private String name;
	
	public Cat(ArrayList<Object> args) {
		numOfLegs = (Integer)args.get(0);
		name = (String)args.get(1);
	}
	
	@Override
	public void makeSound() {
		System.out.println("miau miau");
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public int getNumberOfLegs() {
		return numOfLegs;
	}
}

class Chicken implements Animal{
	private String name;
	private int numOfLegs;
	
	public Chicken(ArrayList<Object> args) {
		numOfLegs = (Integer)args.get(0);
		name = (String)args.get(1);
	}

	@Override
	public void makeSound() {
		System.out.println("ko ko ko");
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public int getNumberOfLegs() {
		return numOfLegs;
	}
}