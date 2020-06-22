package il.co.ilrd.reflection;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class Ex1 
{
	public static void main(String[] args) throws Exception
	{
		AnalizedClass labello = new AnalizedClass();
		Class<?> c = AnalizedClass.class;
		System.out.println("class name: " + c.getName());
		System.out.println("\nsuper class name: " + c.getSuperclass());
		System.out.println("\nModifier or class: " + Modifier.toString(c.getModifiers()));
		
		System.out.println("\nAll interfaces of class:");
		Class<?>[] interfacesArr = c.getInterfaces();
		for (Class<?> class1 : interfacesArr) 
		{			
			System.out.println(class1.toString());
		}
		
		System.out.println("\nAll fields of class:");
		Field[] allFields = c.getDeclaredFields();
		for (Field field : allFields) {
			System.out.println(field.toString());
		}
		
		System.out.println("\nInherited fields: ");
		Field[] inheritedFields = labello.getClass().getFields();
		for (Field field : inheritedFields) {
			System.out.println(field.toString());
		}
		
		System.out.println("\nAll methods: ");
		Method[] classMethods = c.getMethods();
		for (Method method : classMethods) 
		{
			System.out.println(method.toString());
		}

		System.out.println("\nCreating new instance: ");
		try {
			Object instanceFirstWay = c.newInstance();
			Constructor<?> constructor = c.getConstructor(int.class, int.class, int.class);
			Object instanceSecondWay = constructor.newInstance(1,2,3);
			
			Method firstMethod;
			firstMethod = instanceFirstWay.getClass().getMethod("firstFunc");
			firstMethod.invoke(instanceFirstWay);
			
			Method secondMethod;
			secondMethod = instanceSecondWay.getClass().getMethod("secondFunc");
			secondMethod.invoke(instanceSecondWay);
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
