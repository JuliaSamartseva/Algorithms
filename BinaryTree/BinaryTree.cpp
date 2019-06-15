// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

struct node {
	Node* data;
	node* next;

	node(Node* data) {
		this->data = data;
		this->next = NULL;
	}
};

struct Queue { //2_2 Queue of Nodes*

	node* front = NULL;
	node* rear = NULL;
	int size = 0;

	void enqueue(Node* x) {
		node *new_node = new node(x);
		if (front == NULL && rear == NULL) {
			front = new_node;
			rear = new_node;
		}
		else {
			rear->next = new_node;
			rear = new_node;
		}
		size++;
	}

	Node* dequeue() {
		node* temp = front;
		Node* result;
		if (front == NULL) return NULL;
		if (front == rear) {
			result = front->data;
			front = NULL;
			rear = NULL;
			size--;
		}
		else {
			result = front->data;
			front = front->next;
			size--;
		}
		free(temp);
		return result;
	}

	bool isEmpty() {
		if (front == NULL) return true;
		else return false;
	}
};

struct Stack { //11_3 Stack of Nodes*
	node* top = NULL; 

	void push(Node* x) {
		node* new_node = new node(x);
		if (top == NULL) top = new_node; else {
			new_node->next = top;
			top = new_node;
		}
	}

	Node* pop() {
		Node* result;
		if (top == NULL) return NULL; 
		else {
			node* temp = top;
			result = top->data;
			top = top->next;
			free(temp);
			return result;
		}
	}

	Node* peek() {
		return top->data;
	}

	bool isEmpty() {
		if (top == NULL) return true;
		else return false;
	}
};

void postorderIterative(Node* x) { //11_3
	Node* head = x;
	Stack stack;
	stack.push(head);
	bool isLeaf;
	bool finishedSubtrees;
	while (!stack.isEmpty()) {
		Node* next = stack.peek();
		finishedSubtrees = (next->right == head || next->left == head);
		isLeaf = (next->left == NULL && next->right == NULL);
		if (finishedSubtrees || isLeaf) {
			stack.pop();
			std::cout << next->data << " ";
			head = next;
		}
		else {
			if (next->right != NULL) 
				stack.push(next->right);
			if (next->left != NULL) 
				stack.push(next->left);
		}
	}
}

void preorderIterative(Node* x) {
	Stack stack; 
	Node* head = x;
	stack.push(head);
	Node* element;
	while (!stack.isEmpty()) {
		element = stack.pop();
		std::cout << element->data << " ";
		if (element->right)	stack.push(element->right);
		if (element->left) stack.push(element->left);
	}
}

void inorderIterative(Node* x) {
	Stack stack;
	Node* head = x;
	while (head != NULL || !stack.isEmpty()) {
		while (head != NULL) {
			stack.push(head);
			head = head->left;
		}
		head = stack.pop();
		std::cout << head->data << " ";
		head = head->right;
	}
}


void PrintElementsbyLevel(Node* head) { //2_2
	Queue queue;
	int counter;
	Node* temp;
	queue.enqueue(head); // easier to use Stack
	while (!queue.isEmpty()) {
		counter = queue.size;
		while (counter > 0) {
			temp = queue.dequeue();
			counter--;
			std::cout << temp->data << " ";
			if (temp->left != NULL) queue.enqueue(temp->left); 
			if (temp->right != NULL) queue.enqueue(temp->right);
		}
		std::cout << "\n";
	}
}

void PrintRange(Node* node, int u, int v, int& count) { //56_3
	if (node == NULL) return;
	PrintRange(node->left, u, v, count);
	if ((node->data >= u) && (node->data <= v)) count++;
	PrintRange(node->right, u, v, count);
}

int maxDepth(Node* x) { //20_3
	if (x == NULL) return 0; else {
		int ldepth = maxDepth(x->left);
		int rdepth = maxDepth(x->right);
		if (ldepth > rdepth) return ldepth + 1; else
			return rdepth + 1;
	}
}

void searchKeyInorder(Node* x, int key, bool& result) {//17_3
	if (x == NULL) return;
	searchKeyInorder(x->left, key, result);
	if (x->data == key) result = true;
	searchKeyInorder(x->right, key, result);
}

void searchKey(Node* node, int key) { //17_3
	Node* x = node;
	bool result = false;
	searchKeyInorder(x, key, result);
	std::cout << result;
}

void searchKeyMoreInorder(Node* node, int key, int& result) {
	if (node == NULL) return;
	searchKeyMoreInorder(node->left, key, result);
	if (node->data > key) result++;
	searchKeyMoreInorder(node->right, key, result);
}

void searchMoreKey(Node* node, int key) { //54_3
	Node* x = node;
	int result = 0;
	searchKeyMoreInorder(x, key, result);
	std::cout << result;
}

Node* cloneBinaryTree(Node* node) {
	if (node == NULL) return NULL;
	Node* new_node = new Node(node->data);
	new_node->left = cloneBinaryTree(node->left);
	new_node->right = cloneBinaryTree(node->right);
	return new_node;
}

int NodeNumber(Node* x) { //7_4
	if (x == NULL) return 0;
	else return (NodeNumber(x->left) + NodeNumber(x->right) + 1);
}

void Inorder_recur(Node* node, int a, int& result) {
	if (node == NULL) return;
	Inorder_recur(node->left, a, result);
	if (node->data > a) result++;
	Inorder_recur(node->right, a, result);
}

void printInorder(Node* head, int a) {
	Node* x = head;
	int result = 0;
	Inorder_recur(x, a, result);
	std::cout << result;
}

void countLeafNodes_recur(Node* head, int u, int v, int& result) {
	if (head == NULL) return;
	if (head->left == NULL && head->right == NULL) {
		if (head->data <= v && head->data >= u) result++;
		return;
	}
	countLeafNodes_recur(head->left, u, v, result);
	countLeafNodes_recur(head->right, u, v, result);
}

int countLeafNodes(Node* head, int u, int v) {
	int result = 0;
	countLeafNodes_recur(head, u, v, result);
	return result;
}




int main()
{
	Node* head = new Node(8);
	head->left = new Node(7);
	head->right = new Node(6);
	head->right->right = new Node(3);
	head->right->left = new Node(5);
	inorderIterative(head);
}
