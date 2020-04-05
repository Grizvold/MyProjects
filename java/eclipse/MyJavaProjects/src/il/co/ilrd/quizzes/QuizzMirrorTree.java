package il.co.ilrd.quizzes;

public class QuizzMirrorTree {

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
		


		public boolean isBalanced(Node root)
		{
		    return (maxDepth(root) - minDepth(root) <= 1);
		}
		
		public int maxDepth(Node root)
		{
		    if (root == null) return 0;
		
		    return 1 + Math.max(maxDepth(root.leftNode), maxDepth(root.rightNode));
		}
		
		public int minDepth (Node root)
		{
		    if (root == null) return 0;
		
		    return 1 + Math.min(minDepth(root.leftNode), minDepth(root.rightNode));
		}
	}
	
	public static void main(String[] args) {
		QuizzMirrorTree quizz = new QuizzMirrorTree();
 		BinaryTree tree = quizz.new BinaryTree();

 		tree.rootNode = quizz.new Node(10);
		
 		tree.rootNode.rightNode = quizz.new Node(15);
		tree.rootNode.rightNode.leftNode = quizz.new Node(13);
		
		tree.rootNode.leftNode = quizz.new Node(5);
		tree.rootNode.leftNode.rightNode = quizz.new Node(7);
		tree.rootNode.leftNode.leftNode = quizz.new Node(3);
		tree.rootNode.leftNode.leftNode.leftNode = quizz.new Node(1);
		
		tree.printInOrder();
		System.out.println("\nIs balanced?: " + tree.isBalanced(tree.rootNode)); 
		tree.mirror();
		tree.printInOrder();
		
		QuizzMirrorTree quizz2 = new QuizzMirrorTree();
		BinaryTree tree2 = quizz2.new BinaryTree();
		
		tree2.rootNode = quizz.new Node(10);
		
		tree2.rootNode.rightNode = quizz.new Node(15);
		tree2.rootNode.rightNode.leftNode = quizz.new Node(13);
		
		tree2.rootNode.leftNode = quizz.new Node(5);
		tree2.rootNode.leftNode.rightNode = quizz.new Node(7);
		tree2.rootNode.leftNode.leftNode = quizz.new Node(3);
		System.out.println("\n\nSecond tree");
		tree2.printInOrder();
		System.out.println("\nIs balanced?: " + tree2.isBalanced(tree2.rootNode)); 
	}

}
