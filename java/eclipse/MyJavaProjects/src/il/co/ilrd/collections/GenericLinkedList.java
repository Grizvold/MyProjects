package il.co.ilrd.collections;

public class GenericLinkedList<T> {
	
	private GLLNode headNode;
	
	private class GLLNode{
		private T data;
		private GLLNode nextGLLNode;
		
		private GLLNode(T data, GLLNode next){
			this.data = data;
			nextGLLNode = next;
		}
	}
	
	private class GLLIterator implements GenericIterator<T>{

		private GLLNode currentNode;
		
		private GLLIterator(GLLNode node) {
			currentNode = node;
		}
		
		@Override
		public T next() {
			T temp = (T) this.currentNode.data;
			currentNode = currentNode.nextGLLNode;
			
			return temp;
		}

		@Override
		public boolean hasNext() {
			return (null != currentNode.nextGLLNode);
		}
	}
	
	public void pushFront(T data){
		this.headNode = new GLLNode(data, headNode);
	}
	
	public T popFront() {
		T nodeDataT = null;

		if(null != headNode)
		{
			nodeDataT = this.headNode.data;
			headNode = headNode.nextGLLNode;
		}
		return nodeDataT;		
	}
	
	public void clear() {
		headNode = null;
	}
	
	public boolean isEmpty() {
		return (null == this.headNode);
	}
	
	public int getSize() {
		int counter = 0;
		
		GLLIterator iterator = new GLLIterator(headNode);
		
		for(counter = 0; null != iterator.currentNode; ++counter)
		{
			iterator.next();
		}
		
		return counter;
	}
	
	public GLLIterator begin() {
		return (new GLLIterator(headNode));
	}
	
	public GenericIterator<T> find(T data) {
		GLLIterator iterator = new GLLIterator(headNode);
		
		while(null != iterator.currentNode)
		{
			if(iterator.currentNode.data.equals(data))
			{
				return iterator;
			}
			iterator.next();
		}
		
		return null;
	}
}
