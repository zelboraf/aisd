#include <iostream>
using namespace std;

class Graph {
private:
	struct Node {
		int b;
		int w = -1;
		Node* next = nullptr;
	};

	int graph_deg;
	Node** array;

public:
	Graph(int graph_deg) : graph_deg(graph_deg) {
		array = new Node*[graph_deg];
		for (int i = 0; i < graph_deg; i++) {
			array[i] = nullptr;
		}
	}
	~Graph() {
		for (int i = 0; i < graph_deg; i++) {
			while (array[i]) {
				array[i] = array[i]->next;
				delete array[i];
			}
		}
		delete[] array;
	}

	void push(int a, int b, int w) {
		Node* new_node = new Node;
		new_node->b = b;
		new_node->w = w;
		new_node->next = array[a];
		array[a] = new_node;
	}

	int dijkstra(int start, int end) {

	}
};

int main() {
	int graph_deg, edge_count;
	int a, b, w;
	Graph* G = new Graph(graph_deg);

	cin >> graph_deg >> edge_count;
	while (edge_count--) {
		cin >> a >> b >> w;
		G->push(a, b, w);
	}

	int search_count, result;
	int start, end;

	cin >> search_count;
	while (search_count--) {
		result = G->dijkstra(start, end);
		if (result == -1)
			cout << "nie ma";
		else
			cout << result;
	}

	delete G;
	return 0;
}
