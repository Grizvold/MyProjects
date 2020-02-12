package il.co.ilrd.my_tests;

import java.util.ArrayList;
import java.util.function.Function;

import il.co.ilrd.design_pattern.factory.FactoryPattern;

public class FactoryTest {

	public static void main(String[] args) {
		ArrayList<Object> dogArgs = new ArrayList<Object>();
		ArrayList<Object> catArgs = new ArrayList<Object>();
		ArrayList<Object> catByInstance = new ArrayList<Object>();
		ArrayList<Object> chickenArgs = new ArrayList<Object>();
		ArrayList<Object> dogStaticArgs = new ArrayList<Object>();
		FactoryPattern<Animal, String, ArrayList<Object>> factory = new FactoryPattern<>();
		
		dogArgs.add(0, 4);
		dogArgs.add(1, "Rexi");
		dogStaticArgs.add(0, 4);
		dogStaticArgs.add(1, "Garu");
		catArgs.add(0, 4);
		catArgs.add(1, "Yuki");
		catByInstance.add(0, 3);
		catByInstance.add(1, "CrippledCat");
		chickenArgs.add(0, 2);
		chickenArgs.add(1, "Kuki");
		
		factory.add("Dog", arguments->new Dog(dogArgs));
		factory.add("DogStatic", Dog::dogFactoryMethod);
		factory.add("Cat", Cat::new);
		factory.add("Chicken", (arguments)->new Chicken(chickenArgs));
		
		Animal dog = factory.create("Dog", dogArgs);
		Animal catByConstructor = factory.create("Cat", catArgs);
		Animal chicken = factory.create("Chicken", chickenArgs);
		Animal dogByStatic = factory.create("DogStatic", dogStaticArgs);

		factory.add("CatCripple", ((Cat)catByConstructor)::instanceOfExisting);
		Animal catCripple = factory.create("CatCripple", catByInstance);
		
		dog.makeSound();
		
		System.out.println("\n" + catByConstructor.getName());
		catByConstructor.makeSound();
		
		chicken.makeSound();
		
		System.out.println("\n" + dogByStatic.getName());
		
		System.out.println("\n" + catCripple.getName() + " num of legs: " + catCripple.getNumberOfLegs());
		catCripple.makeSound();
		
		
		Reference objReference = new Reference();
		FactoryPattern<Reference, String, Reference> referenceFactory = new FactoryPattern<Reference, String, Reference>();
		referenceFactory.add("reference", Reference::createReference);
		Reference reference = referenceFactory.create("reference", objReference);
		reference.printInReference(" test");
		
		instanceReference(objReference::printInReference);
		
	}
	
	static void instanceReference(Function<String, Integer> args) {
		args.apply("hello");
	}
}

class Reference{
	public Reference createReference() {
		return new Reference();
	}
	
	public int printInReference(String s) {
		System.out.println("inside reference "+ s);
		return 0;
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
	
	public static Dog dogFactoryMethod(ArrayList<Object> args) {
		return new Dog(args);
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
	
	public Cat instanceOfExisting(ArrayList<Object> args) {
		return new Cat(args);
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