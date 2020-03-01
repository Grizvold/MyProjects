package il.co.ilrd.quizzes;

import java.util.LinkedList;

public class LeetCodeAddingTwoNumbers {
	/**
	 * Definition for singly-linked list. */
	 public static class ListNode {
	   int val;
	   ListNode next;
	   ListNode(int x) { 
	    	  val = x; 
	   }
	 }
	 


	public static void main(String[] args) {
		LinkedList<Integer> list1 = new LinkedList<Integer>();
		LinkedList<Integer> list2 = new LinkedList<Integer>();
		list1.push(3);list1.push(4);list1.push(2); //342
		list2.push(4);list2.push(6);list2.push(5); //465
		//System.out.println("My list result: " + addTwoNumbersLinked(list1, list2).toString()); //807
		
		
		ListNode listNode1 = new ListNode(9); 
		listNode1.next = new ListNode(9);
		listNode1.next.next = new ListNode(9);
		listNode1.next.next.next = null;
		
		ListNode listNode2 = new ListNode(1);
		listNode2.next = null;
//		listNode2.next = new ListNode(6);
//		listNode2.next.next = new ListNode(5);
//		listNode2.next.next.next = null;
		
		ListNode result = addTwoNumbers(listNode1, listNode2);
		while(!(result == null)) {
			System.out.println(result.val);
			result = result.next;
		}
	}

	public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
		ListNode resultList = new ListNode(0);
		ListNode headList = resultList;
		int tempSum; 
		int carry = 0;
		ListNode shortList;
		ListNode longList;
		
		if(lenght(l1) > lenght(l2)) {
			longList = l1;
			shortList = l2;
		}
		else {
			longList = l2;
			shortList = l1;
		}
		
		while(!(shortList == null)) {
			tempSum = shortList.val + longList.val + carry;
			if(tempSum >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			resultList.next = new ListNode(tempSum % 10);
			resultList = resultList.next;
			longList = longList.next;
			shortList = shortList.next;
		}
		
		while(!(longList == null)) {
			tempSum = longList.val + carry;
			if(tempSum >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			resultList.next = new ListNode(tempSum % 10);
			resultList = resultList.next;
			longList = longList.next;
		}
		
		if(carry == 1) {
			resultList.next = new ListNode(carry);
			resultList = resultList.next;
		}
		
		return headList.next;
	}
	
	public static int lenght(ListNode list) {
		int size = 0;
		
		while(!(list == null)) {
			list = list.next;
			++size;
		}
		return size;
	}
	
	public static LinkedList<Integer> addTwoNumbersLinked(LinkedList<Integer> list1, 
													LinkedList<Integer> list2){
		LinkedList<Integer> resultList = new LinkedList<Integer>();
		int carry = 0;
		int tempSum;
		int size = list1.size();
		
		for (int i = 0; i < size; ++i) {
			tempSum = list1.pop() + list2.pop() + carry;
			if(tempSum >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			resultList.push((tempSum) % 10);
		}
		return resultList;
	}
	
}
