
public class StaticBinding { 
    public static class superclass { 
        static void print() 
        { 
            System.out.println("print in superclass."); 
        } 
    } 
    public static class subclass extends superclass { 
        static void print() 
        { 
            System.out.println("print in subclass."); 
        } 
    } 
  
    @SuppressWarnings("unused")
	public static void main(String[] args) 
    { 
		superclass A = new superclass(); 
        superclass B = new subclass(); 
        superclass.print(); 
        superclass.print(); 
    } 
} 
