package il.co.ilrd.quizzes;

public class MirrorTree {

	class Node{
		int data;
		Node leftNode, rightNode;
		
		public Node(int value){
			data = value;
			leftNode = rightNode = null;
		}
	}
	
	class BinaryTree{
		Node rootNode;
		
		void mirror() {
			rootNode = mirror(rootNode);
		}
		
		Node mirror(Node node) {
			if(node == null)
			{
				return node;
			}
			
			Node left = mirror(node.leftNode);
			Node right = mirror(node.rightNode);
			
			node.leftNode = right;
			node.rightNode = left;
			
			return node;
		}
		
		void printInOrder() {
			printInOrder(rootNode);
		}
		
		void printInOrder(Node node) {
			if(node == null) {
				return;
			}
			
			printInOrder(node.leftNode);
			System.out.print(node.data + " ");
			printInOrder(node.rightNode);
		}
	}
	
	public static void main(String[] args) {
		MirrorTree quizz = new MirrorTree();
 		BinaryTree tree = quizz.new BinaryTree();

 		tree.rootNode = quizz.new Node(10);
		
 		tree.rootNode.rightNode = quizz.new Node(15);
		tree.rootNode.rightNode.leftNode = quizz.new Node(13);
		
		tree.rootNode.leftNode = quizz.new Node(5);
		tree.rootNode.leftNode.rightNode = quizz.new Node(7);
		tree.rootNode.leftNode.leftNode = quizz.new Node(3);
		tree.rootNode.leftNode.leftNode.leftNode = quizz.new Node(1);
		
		tree.printInOrder();
		tree.mirror();
		System.out.println("\n");
		tree.printInOrder();
	}

}
