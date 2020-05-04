package il.co.ilrd.quizzes;

public class QuizzSLLPlay {
	
	private class LinkedList{
		private Node headNode;
		
		public class Node{
			private int data;
			private Node next;
			
			private Node(int nodeData, Node nextNode) {
				data = nodeData;
				next = nextNode;
			}
		}
		
		public void push(int inputData) {
			headNode = new Node(inputData, headNode);
		}

		public Node nThNodeFromLast_ByLenght(LinkedList userList, int k) {
			int list_Lenght = 0;
			Node temp_Node = userList.headNode;
			
			while(temp_Node != null) {
				temp_Node = temp_Node.next;
				++list_Lenght;
			}
			
			temp_Node = userList.headNode;
			if(k > list_Lenght) {
				return null;
			}
			
			for (int i = 0; i <= list_Lenght; ++i) {
				temp_Node = temp_Node.next;
			}
				
			return temp_Node;
		}
		
		public Node nThNodeFromLast_By2Pointers(LinkedList userList, int k) {
			Node temp_Node = userList.headNode;
			Node head_Node = userList.headNode;
			
			for (int i = 0; i < k; ++i) {
				head_Node = head_Node.next;
			}
			
			while (head_Node != null) {
				temp_Node = temp_Node.next;
				head_Node = head_Node.next;
			}
			
			return temp_Node;
		}
		

		public Node findLoopStart(LinkedList userList) {
			Node fast_runner = userList.headNode;
			Node slow_runner = userList.headNode;
			
			for (;fast_runner != null && slow_runner != null;
					fast_runner = fast_runner.next.next, slow_runner = slow_runner.next) {
				if(fast_runner == slow_runner) {
					break;
				}
			}
			
			slow_runner = headNode;
			while (slow_runner != fast_runner) {
				slow_runner = slow_runner.next;
				fast_runner = fast_runner.next;
			}
			
			return slow_runner;
		}
	}

	public static void main(String[] args) {
		QuizzSLLPlay test_1 = new QuizzSLLPlay();
		LinkedList list_1 = test_1.new LinkedList();
		list_1.push(5);
		list_1.push(6);
		list_1.push(90);
		list_1.push(5);
		list_1.push(2);
		list_1.push(1);
		list_1.push(14);
		System.out.println(list_1.nThNodeFromLast_ByLenght(list_1, 4));
	}
}

