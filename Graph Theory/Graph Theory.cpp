
#include <fstream>
#include <iostream>

enum color { WHITE, GRAY, BLACK };

struct Node {
	int data;
	Node* next;
	Node(int data)
	{
		this->data = data;
		this->next = NULL;
	}
};


struct AdjacencyList {
	Node** head = NULL;
	int Vertices = 0;

	AdjacencyList(int number)
	{
		Vertices = number;
		head = new Node *[Vertices];
		for (int i = 0; i < Vertices; i++) head[i] = NULL;
	}

	AdjacencyList(std::fstream& file) { // read graph from a list of edges
		int source, destination, number;

		if (file.is_open()) {
			int i = 1;
			file >> Vertices; // read vertices number
			head = new Node *[Vertices];
			for (int i = 0; i < Vertices; i++) head[i] = NULL;

			while ((file >> number)) {
				if (i == 1) {
					source = number;
					i++;
				}
				else {
					destination = number;
					Add(source, destination);
					Add(destination, source);
					i = 1;
				}
			}
		}
		file.close();
	}

	void Add(int source, int destination) {
		if (head[source] == NULL) head[source] = new Node(destination);
		else {
			Node* temp = head[source];
			head[source] = new Node(destination);
			head[source]->next = temp;
		}
	}

	int LeafNumber() { //56_5, 14_5
		int result = 0;
		for (int i = 0; i < Vertices; i++)
			if (head[i] != NULL)
				if (head[i]->next == NULL) result++;
		return result;
	}

	bool isEulerian() { //20_5
		Node* x;
		for (int i = 0; i < Vertices; i++) {
			int degree = 0;
			x = head[i];
			while (x != NULL) degree++;
			if (degree % 2 == 1) return false;
		}
		return true;
	}

	bool isConnected() { //19_5
		bool* visited = new bool[Vertices];
		for (int i = 0; i < Vertices; i++)
			visited[i] = false;
		DFS(0, visited);
		for (int i = 0; i < Vertices; i++)
			if (visited[i] == false) return false;
		return true;
	}

	void DFS(int v, bool* visited) {
		visited[v] = true;
		Node* x = head[v];
		while (x != NULL) {
			if (!visited[x->data]) DFS(x->data, visited);
			x = x->next;
		}
	}

	int edgeNumber() { //17_5
		Node* x;
		int edgeNumber = 0;
		for (int i = 0; i < Vertices; i++) {
			x = head[i];
			while (x != NULL)  edgeNumber++;
		}
		edgeNumber = edgeNumber / 2;
	}

	int VertexDegree() {//11_5
		int count;
		int result = 0;
		for (int i = 0; i < Vertices; i++) {
			if (head[i] != NULL) {
				Node* x = head[i];
				count = 0;
				while (x != NULL) {
					count++;
					x = x->next;
				}
				result++;
			}
		}
		return result;
	}

	void print() {
		Node* x;
		for (int i = 0; i < Vertices; i++) {
			std::cout << "\n vertice " << i << " with";
			x = head[i];
			while (x != NULL) {
				std::cout << " " << x->data;
				x = x->next;
			}
		}
	}

	AdjacencyList findSpanningTree() { //2_4
		AdjacencyList result = AdjacencyList(Vertices);
		bool* visited = new bool[Vertices];
		for (int i = 0; i < Vertices; i++) visited[i] = false;
		dfsSpanningTree(0, result, visited);
		return result;
	}

	void dfsSpanningTree(int v, AdjacencyList & result, bool* visited) { //2_4
		Node* x = head[v];
		visited[v] = true;
		while (x != NULL) {
			if (visited[x->data] == false) {
				result.Add(v, x->data);
				result.Add(x->data, v);
				dfsSpanningTree(x->data, result, visited);
			}
			x = x->next;
		}
	}

};






struct AdjacencyMatrix {
	int** adjacencyMatrix = NULL;
	int VerticesNumber = 0;

	AdjacencyMatrix() {
		std::fstream file;
		std::string word, filename;
		filename = "file.txt";
		file.open(filename.c_str());
		int n = 0;
		if (file.is_open())
		{
			file >> n;
			adjacencyMatrix = new int* [n];
			for (int i = 0; i < n; i++) adjacencyMatrix[i] = new int[n];
			for (int i = 0; i < n; i++) // reading matrix from file
				for (int j = 0; j < n; j++) file >> adjacencyMatrix[i][j];
		}
		file.close();
		VerticesNumber = n;
	}

	bool isConnected() {//9_5
		bool* visited;
		for (int i = 0; i < VerticesNumber; i++) visited[i] = false;
		DFS_connected(0, visited);
		for (int i = 0; i < VerticesNumber; i++)
			if (!visited[i]) return false;
		return true;
	}

	void DFS_connected(int v, bool* visited) {
		visited[v] = true;
		for (int i = 0; i < VerticesNumber; i++) {
			if (adjacencyMatrix[v][i] == 1 && !visited[i]) DFS_connected(i, visited);
		}
	}


	bool isCyclic() { //10_5
		int* color = new int[VerticesNumber];
		bool* visited = new bool[VerticesNumber];
		for (int i = 0; i < VerticesNumber; i++) {
			color[i] = WHITE;
			visited[i] = false;
		}
		bool result = false;
		DFS(0, visited, color, result);
		return result;
	}

	void DFS(int v, bool* visited, int* color, bool& result) { //10_5
		visited[v] = true;
		color[v] = GRAY;
		for (int i = 0; i < VerticesNumber; i++) {
			if (adjacencyMatrix[v][i] == 1) {
				if (color[i] == GRAY) result = true; //in a directed graph we check only if color is gray
				else DFS(i, visited, color, result);
			}
		}
		color[v] = BLACK;
	}

	int isolatedNumber() { //13_3
		int result = 0;
		bool isolated;
		for (int i = 0; i < VerticesNumber; i++) {
			isolated = true;
			for (int j = 0; j < VerticesNumber; j++)
				if (adjacencyMatrix[i][j] == 1) isolated = false;
			if (isolated) result++;
		}
		return result;
	}
};



int main()
{
	//2_4
	std::fstream file;
	file.open("file3.txt");
	AdjacencyList x = AdjacencyList(file);
	AdjacencyList result = x.findSpanningTree();
	result.print();
}

