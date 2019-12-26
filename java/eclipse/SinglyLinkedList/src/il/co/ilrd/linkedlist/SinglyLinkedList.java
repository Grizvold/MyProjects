package il.co.ilrd.linkedlist;
/**
 * 
 */

/**
 * @author Ruslan_Gorbaty_FS767
 *
 */

public class SinglyLinkedList 
{
	
	private class Node 
	{
		@SuppressWarnings("unused")
		private Object data;
		private Node next;
		
		private Node(Object data, Node next)
		{
			this.data = data;
			this.next = next;
		}
	}
	
	private class IteratorLinkedList implements GenericIterator 
	{		
		private Node currentNode;
		
		private IteratorLinkedList(Node node)
		{
			currentNode = node;
		}
		
		@Override
		public Object next() 
		{
			Object curr = currentNode;
			currentNode = currentNode.next;
			
			return curr;
		}

		@Override
		public boolean hasNext() 
		{
			return (null != currentNode);
		}
		
		@Override
		public String toString() 
		{
			return "Itr data = " + currentNode.data ;
		}
	}
		
	private Node headNode;
	
	/** -Insert new node to the front of the list. */
	public void pushFront(Object data)
	{
		headNode = new Node(data, headNode);
	}
	
	/** -Remove node from the front of the list.
	 *  -Return status: 
	 *  				true - success
	 *  				false - failure */
	public Object popFront()
	{
		Object nodeData = null;
		
		if (null != headNode)
		{
			nodeData = headNode.data;
			headNode = headNode.next;
			
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
	 * @return
	 */
	public boolean isEmpty() 
	{
		return (null == headNode);
	}
	
	public int getSize() 
	{
		int counter = 0;
		GenericIterator itr = begin();
		
		while (itr.hasNext())
		{
			counter++;
			itr.next();
		}
		
		return (counter);
	}

	public GenericIterator begin() 
	{
		return (new IteratorLinkedList(headNode));
	}
	
	public String toString()
	{
		IteratorLinkedList itr = new IteratorLinkedList(headNode);
		
		return itr.toString();
	}
	
	public GenericIterator find(Object data) 
	{		
		IteratorLinkedList itr = new IteratorLinkedList(headNode);
		
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
