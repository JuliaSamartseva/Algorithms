// CircularLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Node {
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}
};

struct CircularLinkedList {
	Node* last = NULL;

	void insertFront(int data) {
		if (last == NULL) {
			last = new Node(data);
			last->next = last;
		}
		else {
			Node* temp = new Node(data);
			temp->next = last->next;
			last->next = temp;
		}
	}

	void insertEnd(int data) {
		if (last == NULL) {
			last = new Node(data);
			last->next = last;
		}
		else {
			Node* temp = new Node(data);
			temp->next = last->next;
			last->next = temp;
			last = temp;
		}
	}

	void insertAfter(int data) {
		if (last == NULL || (last->data>0 && last->next->data>0)) insertFront(data); // all > 0, no elements
		else 
		{
			Node* x = last->next; //head
			Node* prev = last;
			while (x->data < 0) {
				prev = x;
				x = x->next;
				if (x == last->next) break;
			}
			if (last == prev) insertEnd(data); else
			{
				Node* new_element = new Node(data);
				new_element->next = prev->next;
				prev->next = new_element;
			}
		}
	}

	void print(){
		std::cout << "\n";
		if (last == NULL) std::cout << "List is empty";
		else {
			Node* traverse = last->next;
			do {
				std::cout << traverse->data << " ";
				traverse = traverse->next;
			} while (traverse != last->next);
		}
	}

	CircularLinkedList reverseList() { //10_1
		Node* x = last->next;
		CircularLinkedList result;
		do {
			result.insertFront(x->data);
			x = x->next;
		} while (x != last->next);
	}

	bool isEmpty() {
		if (last == NULL) return true; 
		else return false;
	}

};

CircularLinkedList reorderList(CircularLinkedList x) { //20_1
	CircularLinkedList y;
	Node* traverse_x = x.last->next; //head of the list
	do {
		if (traverse_x->data > 0) y.insertEnd(traverse_x->data); else
			if (traverse_x->data < 0) y.insertFront(traverse_x->data); else
				y.insertAfter(traverse_x->data); //0
		traverse_x = traverse_x->next;
	} while (traverse_x != x.last->next);
	return y;
}

CircularLinkedList mergeLists(CircularLinkedList x, CircularLinkedList y) { //20_1 second option 
	if (x.isEmpty() == true) return y; else
		if (y.isEmpty() == true) return x; else {
			Node* temp = x.last->next; // head of first
			x.last->next = y.last->next;
			y.last->next = temp;
			x.last = y.last;
			return x;
		}
}

CircularLinkedList reorderList2(CircularLinkedList x) { //20_1 second option (with 3 lists)
	CircularLinkedList positive, negative, zero;
	Node* traverse_x = x.last->next; //head of the list
	do {
		if (traverse_x->data > 0) positive.insertFront(traverse_x->data); else
			if (traverse_x->data < 0) negative.insertFront(traverse_x->data); else
				zero.insertFront(traverse_x->data); //0
		traverse_x = traverse_x->next;
	} while (traverse_x != x.last->next);
	CircularLinkedList result;
	result = mergeLists(negative, zero);
	result = mergeLists(result, positive);
	return result;
}



void divideList(CircularLinkedList initial, CircularLinkedList even, CircularLinkedList odd) { //11_1
	Node* x = initial.last->next;
	do {
		if (x->data % 2 == 0) even.insertFront(x->data); else
			odd.insertFront(x->data);
		x = x->next;
	} while (x != initial.last->next);
}


int main()
{
	CircularLinkedList x;
	x.insertFront(9);
	x.insertFront(8);
	x.insertFront(0);
	x.insertFront(88);
	x.insertFront(9);
	x.print();
	x = reorderList2(x);
	x.print();
}
