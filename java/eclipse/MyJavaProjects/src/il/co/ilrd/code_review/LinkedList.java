package il.co.ilrd.code_review;

/****************************
 * dev : galit sharon	    *
 * rev : Ruslan Gorbaty		*
 ***************************/


public class LinkedList {
	
	private Node root;
	
	private class Node {
		
		private Object data;
		private Node next;
		
		Node(Object data, Node next) {
			
			this.data = data;
			this.next = next;
		}	
	}
	
	
	private static class IteratorLL implements Iterator {
		
		private Node currNode;
		
		private IteratorLL(Node node) {
			
			currNode = node;
		}
			
		public Object next() {
			
			if(null == currNode) {
				return null;
			}
			
			Object currData = currNode.data;
			currNode = currNode.next;
			
			return currData;
		}
		
		public boolean hasNext() {
			
			return currNode.next != null;
		}	
	}
	
	
	public void pushFront(Object data) {
		
		root = new Node(data, root);
	}
	
	public Object popFront() {
		
		Node currRoot = root;
		this.root = this.root.next;
		
		return currRoot.data;
	}
	
	
	public Iterator find(Object data) {
		
		IteratorLL iter = new IteratorLL(root);
		
		while(iter.currNode != null) {
			
			if (iter.currNode.data.equals(data)) {
				return iter;
			}
			iter.next();
		}
		
		return null;	
	}
	
	
	public int size() {
		
		Node currNode = root;
		int counter = 0;
				
		while(currNode != null) {
			
			++counter;
			currNode = currNode.next;
		}
		
		return counter;		
	}
	
	
	public boolean isEmpty() {
		
		return (null == root);	
	}
	
	
	public Iterator begin() {
		
		return (new IteratorLL(root));	
	}
}

