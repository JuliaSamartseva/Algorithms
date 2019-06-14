#include <fstream>
#include <iostream>


struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

struct BinarySearchTree {
	Node* head = NULL;
	int NodesNumber = 0;

	void insertNode(int key) { //56_4
		int i = 0;
		Node* x = head;
		Node* element = new Node(key);

		if (head == NULL) head = element; else {
			while (true) {
				if (x->data >= element->data) i = -1;
				else i = 1;
				if (i < 0) {
					if (x->left == NULL) {
						x->left = element;
						break;
					}
					else x = x->left;
				}
				else { // i > 0
					if (x->right == NULL) {
						x->right = element;
						break;
					}
					else x = x->right;
				}
			}
		}
		NodesNumber++;
	}

	Node* minValueNode(Node* element) {
		Node* x = element;
		// find the leftmost node
		while (x->left != NULL) x = x->left;
		return x;
	}

	void deleteNode(int key) {
		Node* x = head;
		head = deleteNode_recur(x, key);
		NodesNumber--;
	}

	Node* deleteNode_recur(Node* node, int key) {
		if (node == NULL) return node;
		if (key < node->data) node->left = deleteNode_recur(node->left, key); //find the right node to delete
		else if (key > node->data) node->right = deleteNode_recur(node->right, key);
		else { // node with this key has been founded
			if (node->left == NULL) // with one or no child
			{
				Node* temp = node->right;
				free(node);
				return temp;
			}
			else if (node->right == NULL)
			{
				Node* temp = node->left;
				free(node);
				return temp;
			}
			// with two children 
			Node* temp = minValueNode(node->right);
			node->data = temp->data;
			node->right = deleteNode_recur(node->right, temp->data);
		}
		return node;
	}

	void printInorder() {
		Node* x = head;
		printInorder_recur(x);
	}

	void printInorder_recur(Node* node) {
		if (node == NULL) return;
		printInorder_recur(node->left);
		std::cout << node->data << " ";
		printInorder_recur(node->right);
	}

	void createInorderArray(Node* node, int* nodes, int& i) {
		if (node == NULL) return;
		createInorderArray(node->left, nodes, i);
		nodes[i] = node->data;
		i++;
		createInorderArray(node->right, nodes, i);
	}

	void balanceBinaryTree() {
		Node* x = head;
		int* nodes = new int[NodesNumber];
		int i = 0;
		createInorderArray(x, nodes, i);
		head = balanceBinaryTree_recur(nodes, 0, NodesNumber - 1);
	}

	Node* balanceBinaryTree_recur(int* nodes, int start, int end) {
		if (start > end)
			return NULL;
		int mid = (start + end) / 2;
		Node * x = new Node(nodes[mid]);
		x->left = balanceBinaryTree_recur(nodes, start, mid - 1);
		x->right = balanceBinaryTree_recur(nodes, mid + 1, end);
		return x;
	}

	void PrintRange(int v, int u) { //20_4
		Node* x = head;
		int result = 0;
		std::cout << " All Nodes from " << v << " to " << u << ":\n";
		PrintRange_recur(x, v, u, result);
		std::cout << "\n Number of Nodes from this range = " << result;
	}

	void PrintRange_recur(Node* x, int v, int u, int& result) { //20_4
		if (x == NULL) return;
		if (x->data >= v) PrintRange_recur(x->left, v, u, result);
		if ((x->data <= u) && (x->data >= v)) {
			std::cout << x->data << " ";
			result++;
		}
		if (x->data <= u) PrintRange_recur(x->right, v, u, result);
	}

	void printPositive() { //19_4
		Node* x = head;
		int result = 0;
		printPositive_recur(x, result);
		std::cout << "\n Number of Nodes from this range = " << result;
	}

	void printPositive_recur(Node* x, int& result) { //19_4
		if (x == NULL) return;
		if (x->data > 0) printPositive_recur(x->left, result);
		if (x->data > 0) {
			std::cout << x->data << " ";
			result++;
		}
		printPositive_recur(x->right, result);
	}

	int findLessKey(int v) { //17_4 10_4
		Node* x = head;
		return findLessKey_recur(x, v);
	}

	int findLessKey_recur(Node* x, int v) { //17_4 10_4
		if ((x->left == NULL) && (x->right == NULL) && (x->data > v)) return -1; //error, no such key
		if ((x->data < v && x->right == NULL) || (x->data < v && x->right->data >= v)) return x->data;
		if (x->data >= v) return findLessKey_recur(x->left, v);
		else return findLessKey_recur(x->right, v);
	}

	int findMoreKey(int a) { //10_4
		Node* x = head;
		return findMoreKey_recur(x, a);
	}

	int findMoreKey_recur(Node* x, int a) { //10_4
		if (x->left == NULL && x->right == NULL) return -1; //no such key found
		if ((x->data > a && x->left->data <= a) || (x->data > a && x->left == NULL)) return x->data;
		if (x->data <= a) return findLessKey_recur(x->right, a);
		else findLessKey_recur(x->left, a);
	}

	int findMinKey() { //54_4
		Node* x = head;
		while (x->left != NULL) x = x->left;
		return x->data;
	}

	int sumMore(int v) { //11_4
		Node* x = head;
		int result = 0;
		sumMore_recur(x, v, result);
		return result;
	}

	void sumMore_recur(Node* x, int v, int& result) { //11_4
		if (x == NULL) return;
		if (x->data > v) sumMore_recur(x->left, v, result);
		if (x->data > v) result = result + x->data;
		sumMore_recur(x->right, v, result);
	}

};

void insertInorder_recur(Node* node, BinarySearchTree& result) { //2_5
	if (node == NULL) return;
	insertInorder_recur(node->left, result);
	result.insertNode(node->data);
	insertInorder_recur(node->right, result);
}

BinarySearchTree mergeTrees(BinarySearchTree x, BinarySearchTree y) { //2_5
	BinarySearchTree result = x;
	insertInorder_recur(y.head, result);
	return result;
}



int main()
{
	BinarySearchTree x;
	x.insertNode(10);
	x.insertNode(3);
	x.insertNode(12);
	x.insertNode(2);
	x.insertNode(5);
	x.insertNode(11);
	x.insertNode(15);
	std::cout << x.findMoreKey(9);
}