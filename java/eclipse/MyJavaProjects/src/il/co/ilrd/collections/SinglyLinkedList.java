package il.co.ilrd.collections;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Hadas Jakoubovitsh
 * @Group       FS767
 * @Description Implementation of Singly Linked List.
 */

public class SinglyLinkedList 
{
	
	private Node headNode;

	private class Node 
	{
		private Object data;
		private Node nextNode;
		
		private Node(Object data, Node nextNode)
		{
			this.data = data;
			this.nextNode = nextNode;
		}
	}
	
	private static class IteratorLinkedList implements GlobalIterator 
	{		
		private Node currentNode;
		
		private IteratorLinkedList(Node node)
		{
			this.currentNode = node;
		}
		
		@Override
		public Object next() 
		{
			Object returnObject = this.currentNode.data;
			this.currentNode = this.currentNode.nextNode;
			
			return returnObject;
		}

		@Override
		public boolean hasNext() 
		{
			return (null != this.currentNode.nextNode);
		}
		
		@Override
		public String toString() 
		{
			return "Itr data = " + currentNode.data ;
		}
	}	
	
	/**
	 * 
	 * -Insert new node to the front of the list.
	 * @param Object data.
	 */
	public void pushFront(Object data)
	{
		this.headNode = new Node(data, headNode);
	}
	
	/**
	 * 
	 * @return Object data.
	 */
	public Object popFront()
	{
		Object nodeData = null;
		
		if (null != headNode)
		{
			nodeData = this.headNode.data;
			headNode = this.headNode.nextNode;
			
			return nodeData;
		}
		
		return null;
	}
	
	public void clear() 
	{
		headNode = null;
	}
	
	/**
	 * 
	 * @return true if empty, false if not empty.
	 */
	public boolean isEmpty() 
	{
		return (null == this.headNode);
	}
	
	/**
	 * 
	 * @return Size of linked list.
	 */
	public int getSize() 
	{
		int counter = 0;

		IteratorLinkedList iteratorLinkedList = new IteratorLinkedList(headNode);
		
		for (counter = 0; null != iteratorLinkedList.currentNode; ++counter) 
		{
			iteratorLinkedList.next();
		}
		
		return (counter);
	}

	/**
	 * 
	 * @return Iterator to the head node of the list.
	 */
	public GlobalIterator begin() 
	{
		return (new IteratorLinkedList(this.headNode));
	}
	
	/**
	 * @return Returns text representation of first node in linked list.
	 */
	public String toString()
	{
		IteratorLinkedList itr = new IteratorLinkedList(headNode);
		
		return itr.toString();
	}
	
	/**
	 * 
	 * @param Object data.
	 * @return Returns iterator if found, if not found returns null.
	 */
	public GlobalIterator find(Object data) 
	{		
		IteratorLinkedList itr = new IteratorLinkedList(this.headNode);
		
		while (null != itr.currentNode) 
		{
			if(itr.currentNode.data.equals(data))
			{
				return itr;
			}
			
			itr.next();
		}
		
		return null;
	}
	
}
