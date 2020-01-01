package il.co.ilrd.code_review;

public class Main {
	
	public static void main(String[] args) {
		
		pushFrontAndBeginTest();
		popFrontTest();
		findTest();
		sizeTest();
		isEmptyTest();
		iteratorTest();
	}
	
	
	static void testFunc(String testName, boolean x) {
		
		if(x) {
			System.out.println(testName + ": success"); 
		} else {
			
			System.out.println(testName + ": fail"); 
		}
	}
	
	
	static void pushFrontAndBeginTest() {
		
		LinkedList sll = new LinkedList();
		boolean before = sll.isEmpty();
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
		
		testFunc("pushFrontAndBeginTest", 
				(Integer)sll.begin().next() == 3 
				&& sll.size() == 4 && before == true);
	}
	
	
	static void popFrontTest() {
			
		LinkedList sll = new LinkedList();
		boolean before = false;
		boolean after = false;
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
		
		before = sll.isEmpty();
		
		for (int i = 0; i < 4; ++i) {
			sll.popFront();
		}
		
		after = sll.isEmpty();
		
		testFunc("popFrontTest", 
				sll.begin().next() == null 
				&& before == false 
				&& after == true);	
	}
	
	
	static void findTest() {
		
		LinkedList sll = new LinkedList();
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
	
		testFunc("findTest", 
				(Integer)sll.find(1).next() == 1 
				&& (Integer)sll.find(2).next() == 2);		
	}	
	
	
	static void sizeTest() {
			
		LinkedList sll = new LinkedList();
		int sizeBefore = sll.size();
		
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
		
		testFunc("sizeTest", 
				(Integer)sll.size() == 4 && sizeBefore == 0);	
	}
	
	
	static void isEmptyTest() {
		
		LinkedList sll = new LinkedList();
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
	
		testFunc("isEmptyTest", (Boolean)sll.isEmpty() == false);	
	}
	
	
	
	static void iteratorTest() {
		
		LinkedList sll = new LinkedList();
		
		for (int i = 0; i < 4; ++i) {
			Integer data = i;
			sll.pushFront(data);
		}
		
		testFunc("iteratorTest", (Boolean)sll.begin().hasNext() == true);	
	}
}
