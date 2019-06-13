// DoublyLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Node {
	int data;
	Node* next;
	Node* prev;
	
	Node(int data) {
		this->data = data;
		this->next = NULL;
		this->prev = NULL;
	}
};

struct DoublyLinkedList {
	Node* head = NULL;

	void insertEnd(int data) {
		if (head == NULL) head = new Node(data);
		else {
			Node* x = head;
			while (x->next != NULL) x = x->next;
			Node* new_node = new Node(data);
			x->next = new_node;
			new_node->prev = x;
		}
	}

	void insertFront(int data) {
		if (head == NULL) head = new Node(data);
		else {
			Node* new_node = new Node(data);
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
	}

	void deleteNode(Node *x) { //56_1	
		if (head == NULL) return;
		if (head == x) head = head->next;
		if (x->next != NULL) x->next->prev = x->prev;
		if (x->prev != NULL) x->prev->next = x->next;
		free(x);
	}

	void deletekeyNode(int key) { //56_1
		Node* current = head;
		Node* next;
		while (current != NULL) {
			if (current->data == key) {
				next = current->next;
				deleteNode(current);
				current = next;
			} else
			current = current->next;
		}
	}

	void deleteAllMin() { //56_1
		int min = head->data;
		Node* x = head->next;
		while (x != NULL) {
			if (x->data < min) min = x->data;
			x = x->next;
		}
		deletekeyNode(min);
	}

	void printList() {
		Node* x = head;
		std::cout << "\n";
		while (x != NULL) {
			std::cout << x->data << " ";
			x = x->next;
		}
	}

	DoublyLinkedList reverseList() { //17_1
		DoublyLinkedList result;
		Node* x = head;
		while (x != NULL) {
			result.insertFront(x->data);
			x = x->next;
		}
		return result;
	}
};

int main()
{
	DoublyLinkedList x;
	x.insertEnd(1);
	x.insertEnd(2);
	x.insertEnd(3);
	x.printList();
	DoublyLinkedList y = x.reverseList();
	y.printList();
}
