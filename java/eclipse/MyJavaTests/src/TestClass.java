import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Constructor;

/**
 * 
 */

/**
 * @author student
 *
 */

class superclass { 
        static void print() 
        { 
            System.out.println("print in superclass."); 
        } 
    } 
class subclass extends superclass { 
    
	static void print() 
    { 
            System.out.println("print in subclass."); 
        } 
    } 


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

	public static void main(String[] args) throws IOException {
		Parent xParent = new Child();
		System.out.println(((Child)xParent).cityString);
		System.out.println(((Child)xParent).i);
		
		superclass A = new superclass();
		subclass B = new subclass();
		
		A.print();
		B.print();
		
		File linuxDictionary = new File("/home/student/linux_dictionary");
		BufferedReader bufferedReader = new BufferedReader(new FileReader(linuxDictionary));
		String dictionaryString;
		String dictionaryLineString = "";
		while ((dictionaryString = bufferedReader.readLine()) != null) {
			System.out.println(dictionaryString);
			//dictionaryLineString = dictionaryLineString + dictionaryString;
		}
		/*dictionaryLineString.replaceAll("\r", "").replaceAll("\n", "");
		System.out.println(dictionaryLineString);*/
	}	
}
