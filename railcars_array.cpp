#include <iostream>
#define SIZE 4		// initial array size
using namespace std;

class Stack {
private:
	int array_size;
	int stack_ptr;
	int* array;
public:
	Stack() : array_size(SIZE), stack_ptr(0), array(new int[SIZE]) {}
	~Stack() { delete[] array; }

	void resize(int new_array_size) {
			int* new_array = new int[new_array_size];
			for (int i = 0; i < stack_ptr; i++) {
				new_array[i] = array[i];
			}
			delete[] array;
			array = new_array;
			array_size = new_array_size;
	}
	void push(int input) {
		if (stack_ptr == array_size) {
			resize(array_size * 2);		// grow array
		}
		array[stack_ptr] = input;
		stack_ptr++;
	}
	int top() {
		if (stack_ptr) {
			return array[stack_ptr - 1];
		}
		else {
			return 0;
		}
	}
	void pop() {
		if (stack_ptr) {
			stack_ptr--;
		}
		if ((stack_ptr < array_size / 4) && (stack_ptr > 2)) {
			resize(array_size / 4);		// shrink array
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
