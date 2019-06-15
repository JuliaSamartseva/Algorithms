
#include <iostream>

struct Node {
	int data;
	int index;
	Node* next;

	Node(int data, int index) {
		this->data = data;
		this->next = NULL;
		this->index = index;
	}
};

struct LinkedList {
	Node* head = NULL;
    int lastIndex = 0;

	void insertFront(int data) {
		if (head == NULL) head = new Node(data , lastIndex++);
		else {
			Node* new_node = new Node(data, lastIndex++);
			new_node->next = head;
			head = new_node;
		}
	}

	void insertEnd(int data) {
		if (head == NULL) head = new Node(data, lastIndex++);
		else {
			Node* x = head;
			while (x->next != NULL) x = x->next;
			x->next = new Node(data, lastIndex++);
		}
	}

	void insertEnd(int data, int index) {
		if (head == NULL) head = new Node(data, index);
		else {
			Node* x = head;
			while (x->next != NULL) x = x->next;
			x->next = new Node(data, index);
		}
	}

	void printList() {
		Node* x = head;
		std::cout << "\n";
		while (x != NULL) {
			std::cout << x->data << "(" << x->index << ")" << " ";
			x = x->next;
		}
	}

	LinkedList toSparseList() { //56_2
		Node* x = head;
		LinkedList sparseList;
		while (x != NULL) {
			if (x->data != 0) sparseList.insertEnd(x->data, x->index);
			x = x->next;
		}
		return sparseList;
	}

	bool isEmpty() {
		if (head == NULL) return true;
		else return false;
	}
};


struct IndexList { 
	LinkedList* pointers;
	int elementNumber = 0;

	IndexList() { //20_2
		pointers = new LinkedList[100];
		int number, element;
		int index = 0;
		std::cout << "How many elements?";
		std::cin >> number;

		for (int i = 0; i < number; i++) {
			std::cin >> element;
			pointers[element % 100].insertEnd(element, index++);
		}
	}

	void addElement(int v) { //19_2
		pointers[v % 100].insertEnd(v);
	}

	void deleteElement(int v) {//20_2
		Node* head = pointers[v % 100].head;
		Node* temp;
		if (head == NULL) return;
		while (head->data == v) {
			pointers[v % 100].head = head->next;
			free(head);
			head = pointers[v % 100].head;
			if (head == NULL) return;
		}
		while (head->next != NULL) {
			if (head->next->data == v) {
				Node* temp = head->next;
				head->next = temp->next;
				free(temp);
				return;
			} else
			head = head->next;
		}
	}
};

struct IndexMatrix {
	LinkedList* pointers;
	int n, m = 0;

	IndexMatrix() { //13_2
		std::cout << "Dimentions of matrix \n" << " (rows) n = ";
		std::cin >> n;
		std::cout << " (columns) m = ";
		std::cin >> m;
		int element;
		pointers = new LinkedList[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				std::cin >> element;
				if (element != 0) pointers[i].insertEnd(element, j);
			}
	}

	int findMax() { //13_2
		int max = 0;
		for (int i = 0; i < n; i++) {
			Node* x = pointers[i].head;
			while (x != NULL) {
				if (x->data > max) max = x->data;
				x = x->next;
			}
		}
		return max;
	}
};

int main()
{
	//LinkedList x;
	//x.insertEnd(1);
	//x.insertEnd(2);
	//x.insertEnd(3);
	//x.insertEnd(0);
	//x.insertEnd(5);
	//x.printList();
	//LinkedList y = x.toSparseList();
	//y.printList();

	IndexMatrix x;
	std::cout << x.findMax();
}

