/**
 * 
 */

/**
 * @author student
 *
 */

 class Ruslan{
	final int x;
	
	{
		x = 5;
	}
	
	Ruslan()
	{
		
	}
	
	@Override
	public String toString() 
	{
		// TODO Auto-generated method stub
		return "test toString" + "value of x" + x;
	}
}


public class TestClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*Integer one = new Integer(1);
		Integer anotherOne = new Integer(1);
		
		int one = 1;
		int anotherOne = 1;
		
		if(one.equals(anotherOne))
		{
			System.out.println("equal");
		}
		else
		{
			System.out.println("not equal");
		}*/
		
		short s1 =3;
		short s2 = 4;
		short s3 = (short) (s1 & s2);
		Ruslan rusTest = new Ruslan();
		
		System.out.println(s3);
		System.out.println(rusTest);
		//rusTest.toString();
	}

}
