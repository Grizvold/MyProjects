package il.co.ilrd.linkedlist;

import java.io.Console;

import org.omg.CORBA.PRIVATE_MEMBER;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Hadas Jakoubovitsh
 * @Group       FS767
 * @Description Tests of Singly Linked List.
 */

public class SinglyLinkedListTest 
{
	private static final String successString = "SUCCESS";
	private static final String failureString = "FAILURE";
	
	public static void main(String[] args) 
	{
		SinglyLinkedList testLinkedList = new SinglyLinkedList();
		
		System.out.println("Test result for: pushFront: " + pushFrontTest(testLinkedList));
		//System.out.println("Test result for: popFront: " + popFrontTest(testLinkedList));
		//System.out.println("Test result for: find: " + findTest(testLinkedList));
		
		testLinkedList.clear();
	}

	private static String findTest(SinglyLinkedList list) 
	{
		boolean isSuccess = true;
		Integer testVar1 = new Integer(1);
		Integer testVar2 = new Integer(2);
		Integer testVar3 = new Integer(3);
		Integer testVar4 = new Integer(4);

		for(int i = 0; i < 10; i++)
		{
			list.pushFront(i);
		}
		
		System.out.println(list.find(5).next().equals(5));
		
		for(int i = 0; i < 10; i++)
		{
			System.out.println(list.popFront());
		}
		
		
		
		
		if(isSuccess)
		{
			return successString;
		}
		
		return failureString;
	}

	private static String pushFrontTest(SinglyLinkedList list)
	{
		boolean isSuccess = true;
		Integer testVar1 = new Integer(1);
		Integer testVar2 = new Integer(2);
		
		isSuccess &= (true == list.isEmpty());
		list.pushFront(testVar1);
		isSuccess &= (1 == list.getSize());
		/*list.pushFront(testVar2);
		isSuccess &= (2 == list.getSize());
		isSuccess &= (false == list.isEmpty());*/
		
		if(isSuccess)
		{
			return successString;
		}
		
		return failureString;
	}
	
	private static String popFrontTest(SinglyLinkedList list)
	{
		boolean isSuccess = true;
		
		isSuccess &= (false == list.isEmpty());
		isSuccess &= (list.popFront().equals(2));
		isSuccess &= (list.popFront().equals(1));
		isSuccess &= (true == list.isEmpty());
		
		if(isSuccess)
		{
			return successString;
		}
		
		return failureString;
	}
}









