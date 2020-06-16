package il.co.ilrd.quizzes;

import java.util.LinkedList;
import java.util.Queue;

public class QuizzPrintingBinaryTree {

	class Node{
		int node_value;
		Node left_child, right_child;
		
		public Node(int value) {
			node_value = value;
			left_child = right_child = null;
			//TODO: set hight 
		}
	}
	
	class BinaryTree{
		Node root_Node;
		
		public BinaryTree() {
			root_Node = null;
		}
		
		public BinaryTree(int value) {
			root_Node = new Node(value);
		}
		
		private Node addRecursive(Node current_node, int value) {
			if(current_node == null) {
				return new Node(value);
			}
			
			if(value < current_node.node_value) {
				current_node.left_child = addRecursive(current_node.left_child, value);
			}
			else if (value > current_node.node_value) {
				current_node.right_child = addRecursive(current_node.right_child, value);
			}
			else {
				//already exists
				return current_node;
			}
			
			return current_node;
		}
		
		public void addNode(int value) {
			root_Node = addRecursive(root_Node, value);
		}
		
		public void traverseInOrder(Node node) {
			if(node != null) {
				traverseInOrder(node.left_child);
				System.out.println(" " + node.node_value);
				traverseInOrder(node.right_child);
			}
		}
		
		public void traversePreOrder(Node node) {
			if(node != null) {
				System.out.println(" " + node.node_value);
				traversePreOrder(node.left_child);
				traversePreOrder(node.right_child);
			}
		}
		
		public void traversePostOrder(Node node) {
			if (node != null) {
				traversePostOrder(node.left_child);
				traversePostOrder(node.right_child);
				System.out.println(" " + node.node_value);
			}
		}
		
		public void traverseByLevel() {
			if(root_Node == null) {
				return;
			}
			
			Queue<Node> nodes_queue = new LinkedList<>();
			nodes_queue.add(root_Node);
			
			while (!nodes_queue.isEmpty()) {
				
				Node node = nodes_queue.remove();
				
				System.out.print(" " + node.node_value);
				
				if(node.left_child != null) {
					nodes_queue.add(node.left_child);
				}
				
				if(node.right_child != null) {
					nodes_queue.add(node.right_child);
				}
			}
		}
	}
	
	
	
	public static void main(String[] args) {
		QuizzPrintingBinaryTree quizz = new QuizzPrintingBinaryTree();
		BinaryTree smallTree = quizz.new BinaryTree();
		
		smallTree.addNode(6);
		smallTree.addNode(4);
		smallTree.addNode(8);
		smallTree.addNode(3);
		smallTree.addNode(5);
		smallTree.addNode(7);
		smallTree.addNode(9);
		
		smallTree.traverseByLevel();
		System.out.println("\n");
		smallTree.traversePostOrder(smallTree.root_Node);
		System.out.println("\n");
		smallTree.traverseInOrder(smallTree.root_Node);
		System.out.println("\n");
		smallTree.traversePreOrder(smallTree.root_Node);
	}

}
