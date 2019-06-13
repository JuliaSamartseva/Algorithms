// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

struct Node {
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}
};


void swap(Node* x, Node* y) {
	int temp = x->data;
	x->data = y->data;
	y->data = temp;
}

struct LinkedList {
	Node* head = NULL;

	void insertFront(int data) {
		if (head == NULL) head = new Node(data); 
		else {
			Node* new_node = new Node(data);
			new_node->next = head;
			head = new_node;
		}
	}

	void insertEnd(int data) {
		if (head == NULL) head = new Node(data);
		else {
			Node* x = head;
			while (x->next != NULL) x = x->next;
			x->next = new Node(data);
		}
	}

	void printList() {
		Node* x = head;
		std::cout << "\n";
		while (x != NULL) {
			std::cout << x->data << " ";
			x = x->next;
		}
	}

	void bubbleSort() { //9_1
		if (head == NULL) return;
		bool isSorted = false;
		Node* lastUnsorted = NULL;
		Node* ptr = head;
		while (!isSorted) {
			isSorted = true;
			ptr = head;
			while (ptr->next != lastUnsorted) {
				if (ptr->data > ptr->next->data) {
					swap(ptr, ptr->next);
					isSorted = false;
				}
				ptr = ptr->next;
			}
			lastUnsorted = ptr;
		}
	}

	void rearrangeList() { //19_1
		if (head == NULL) return;
		bool isSorted = false;
		Node* lastUnsorted = NULL;
		Node* ptr = head;
		while (!isSorted) {
			isSorted = true;
			ptr = head;
			while (ptr->next != lastUnsorted) {
				if (priority(ptr->data) > priority(ptr->next->data)) {
					swap(ptr, ptr->next);
					isSorted = false;
				}
				ptr = ptr->next;
			}
			lastUnsorted = ptr;
		}
	}

	int priority(int x) { //19_1
		if (x == 0) return 3;
		if (x > 0) return 1;
		if (x < 0) return 3;
	}

};

LinkedList findIntersection(LinkedList x, LinkedList y) { //7_1
	Node* pointer_x = x.head;
	Node* pointer_y = y.head;
	LinkedList result;
	while (pointer_x != NULL && pointer_y != NULL) {
		if (pointer_x->data > pointer_y->data) pointer_y = pointer_y->next;
		else if (pointer_x->data < pointer_y->data) pointer_x = pointer_x->next;
		else {
			result.insertEnd(pointer_x->data);
			pointer_x = pointer_x->next;
			pointer_y = pointer_y->next;
		}
	}
	return result;
}

int main()
{
	LinkedList x;
	x.insertFront(0);
	x.insertFront(0);
	x.insertFront(8);
	x.insertFront(1);
	x.insertFront(-1);
	x.insertFront(0);
	x.printList();
	x.rearrangeList();
	x.printList();
}

//bool isDigit(char x) {
//	if (x <= '9' && x >= '1') return true;
//	else return false;
//}
//
//LinkedList evaluatePolynomial() {
//	std::fstream file;
//	std::string filename;
//	std::string token;
//	filename = "polynom.txt";
//	file.open(filename);
//	if (file.is_open())
//	{
//		std::string polynomial;
//		file >> polynomial;
//		std::string x = "";
//		for (int i = 0; i < polynomial.length(); i++) {
//			token = polynomial[i];
//			if (isDigit(polynomial[i])) {
//				x.append(token);
//			}
//			else {
//
//			}
//		}
//	}
//}