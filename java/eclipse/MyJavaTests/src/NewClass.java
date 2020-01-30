public class NewClass { 
	
    public class superclass { 
    	int x = 6;
    	{
    		System.out.println(x);
    	}
    	
    	 superclass() {
			System.out.println("default parent");
			System.out.println(x);
		}
    	
    	 superclass(int y) {
    		System.out.println("second of parent");
    		this.x = y;
    		this.print();
		}
    	
         void print() 
        { 
            System.out.println("print in superclass."); 
        } 
    } 
    
    public class subclass extends superclass { 
    	int x = 3;
    	{
    		System.out.println(x);
    	}
    	
    	 subclass() {
    		this("something");
    		//super(2);
    		System.out.println(x);
    		System.out.println("resume default ctor");
		}
    	 
    	 subclass(String name)
    	 {
    		 System.out.println("2nd ctor " + name);
    		 System.out.println(this.x);
    	 }
    	
    	@Override
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
        /*superclass A = N.new superclass(); 
        superclass B = N.new subclass(); 
        A.print(); 
        B.print(); 
        //B.foo();
        System.out.println(A.x);
        System.out.println(B.x);  */
        
        subclass C = N.new subclass();
        System.out.println(C.x);
    } 
} 
