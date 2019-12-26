package il.co.ilrd.linkedlist;

import java.io.Console;

/**
 * @author      Ruslan Gorbaty <address @ example.com>
 * @version     1.6                 (current version number of program)
 * @since       1.2          (the version of the package this class was first added to)
 */
public class SinglyLinkedListTest 
{

	/**
	 * @param args
	 */
	
	private static final String successString = "SUCCESS";
	private static final String failureString = "FAILURE";
	
	public static void main(String[] args) 
	{
		SinglyLinkedList testLinkedList = new SinglyLinkedList();
		System.out.println("Test result for: pushFront: " + pushFrontTest(testLinkedList));
		//System.out.println("Test result for: popFront: " + popFrontTest(testLinkedList));
	}

	public static String pushFrontTest(SinglyLinkedList list)
	{
		boolean isSuccess = true;
		Integer testVar1 = new Integer(1);
		Integer testVar2 = new Integer(2);
		
		isSuccess &= (true == list.isEmpty());
		list.pushFront(testVar1);
		isSuccess &= (1 == list.getSize());
		list.pushFront(testVar2);
		isSuccess &= (2 == list.getSize());
		isSuccess &= (false == list.isEmpty());
		//System.out.println("\033[0;34m" + testLinkedList.toString() + "\033[0m");
		//System.out.println(ConsoleColors.RED + list.toString() + ConsoleColors.RESET);
		//System.out.println(ConsoleColors.RED + "test " + ConsoleColors.RESET + " end of test");
		
		if(isSuccess)
		{
			return successString;
		}
		
		return failureString;
	}
	
	/*public static String popFrontTest()
	{
		boolean isSuccess = true;
		SinglyLinkedList testLinkedList = new SinglyLinkedList();
		Integer testVar1 = new Integer(1);
		Integer testVar2 = new Integer(2);
		
		isSuccess &= (true == testLinkedList.isEmpty());
		testLinkedList.pushFront(testVar1);
		isSuccess &= (1 == testLinkedList.getSize());
		isSuccess &= (testVar1.equals(testLinkedList.popFront()));
		System.out.println(isSuccess);
		isSuccess &= (0 == testLinkedList.getSize());
		testLinkedList.pushFront(testVar2);
		System.out.println(testLinkedList.toString());
		
		if(isSuccess)
		{
			return successString;
		}
		
		return failureString;
	}*/
}









