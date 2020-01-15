public class NewClass { 
    public class superclass { 
    	int x = 6;
         void print() 
        { 
            System.out.println("print in superclass."); 
        } 
    } 
    public class subclass extends superclass { 
    	int x = 3;
    	
         void print() 
        { 
        	 System.out.println(x);
            System.out.println("print in subclass."); 
        } 
         
        public void foo() {
        	System.out.println("foo");
        }
    } 
  
    public static void main(String[] args) 
    { 
    	NewClass N = new NewClass();
        superclass A = N.new superclass(); 
        superclass B = N.new subclass(); 
        A.print(); 
        B.print(); 
        //B.foo();
        System.out.println(A.x);
        System.out.println(B.x);  
    } 
} 
