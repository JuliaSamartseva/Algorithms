// AVL Trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Node {
	int data;
	Node* left;
	Node* right;
	int height;

	Node(int data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->height = 1; // new node is added as a leaf
	}

	int getBalance() {
		return abs(this->left->height - this->right->height);
	}

};

int getHeight(Node* x) {
	if (x == NULL) return -1;
	else  return x->height;
}



struct AVL {
	Node* head = NULL;

	void insertNode(int data) {
		Node* x = head;
		Node* element = new Node(data);
		head = insertNode(x, element);
	}

	Node* insertNode(Node* x, Node* element) {
		if (x == NULL) return element;
		if (x->data > element->data) x->right = insertNode(x->right, element); 
		if (x->data < element->data) x->left = insertNode(x->left, element);

		//balance + rotations
	}
};

int main()
{

}

