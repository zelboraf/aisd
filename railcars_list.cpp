#include <iostream>
using namespace std;

class Stack {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;
public:
	Stack() : head(nullptr) {}
	~Stack() { clear_all(); }

	void push(int input) {
		Node* new_node = new Node;
		new_node->value = input;
		new_node->next = head;
		head = new_node;
	}
	void pop() {
		Node* old_head = head;
		head = head->next;
		delete old_head;
	}
	int top() {
		if (head) {
			return head->value;
		}
		else {
			return 0;
		}
	}
	void clear_all() {
		while (head) {
			pop();
		}
	}
};

int main() {
	int input, output = 0, max_value, index = 0;
	Stack S;
	cin >> max_value;

	while (index < max_value) {
		cin >> input;
		if (output == S.top() - 1) {
			S.pop();
			output++;
		}
		else {
			if (output == input - 1) {
				output++;
			}
			else {
				S.push(input);
			}
			index++;
		}
	}
	while (output < max_value) {
		if (output == S.top() - 1) {
			S.pop();
			output++;
		}
		else {
			cout << "NIE\n";
			return 0;
		}
	}
	cout << "TAK\n";
	return 0;
}

// 5 4 2 1 3
