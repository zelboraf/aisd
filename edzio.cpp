#include <iostream>
using namespace std;

class Board {
private:
	char** array;
	int x_size;
	int y_size;

public:
	Board(int x, int y) : x_size(x), y_size(y) {
		array = new char*[x_size];
		for (int i = 0; i < x_size; i++) {
			array[i] = new char[y_size];
		}
	}
	~Board() {
		for (int i = 0; i < x_size; i++) {
			delete[] array[i];
		}
		delete[] array;
	}

	void poke(int x, int y, char input_char) {
		array[x][y] = input_char;
	};
	char peek(int x, int y) {
		return array[x][y];
	};
};

class Edzio {
private:
	struct Segment {
		char colour;
		Segment* next;
		Segment* prev;
	};

	int x, y, x_max, y_max;
	Segment* current;

public:
	Edzio(int edzio_size, int xm, int ym)
	: x(0), y(0), x_max(xm), y_max(ym), current(nullptr) {
		for (int i = 0; i < edzio_size; i++) {
			grow();
		}
	}
	~Edzio() {
		while (current) {
			shrink();
		}
	}

	void grow() {
		Segment* new_Segment = new Segment;
		new_Segment->colour = '.';
		if (current) {
			current->next->prev = new_Segment;
			new_Segment->next = current->next;
			new_Segment->prev = current;
			current->next = new_Segment;
		}
		else {
			current = new_Segment;
			new_Segment->next = current;
			new_Segment->prev = current;
		}
	}
	void shrink() {
		if (current != current->next) {
			current->next->prev = current->prev;
			current->prev->next = current->next;
			Segment* temp = current->next;
			delete current;
			current = temp;
		}
		else {
			delete current;
			current = nullptr;
		}
	}
	void move(char direction, Board *& B) {
		int next_x = x, next_y = y;
		char next_field;
		switch (direction) {
			case 'p' : if (x < x_max - 1) next_x++; else return; break;
			case 'l' : if (x > 0)         next_x--; else return; break;
			case 'd' : if (y < y_max - 1) next_y++; else return; break;
			case 'g' : if (y > 0)         next_y--; else return; break;
		}
		next_field = B->peek(next_x, next_y);
		if (next_field != 'T') {
			if (next_field == 'G') {
				grow();
				next_field = '.';
			}
			current = current->next;
			if (next_field == 'K') {
				shrink();
			}
			if (is_alive()) {
				if (next_field == '.') {
					B->poke(next_x, next_y, current->colour);
				}
				else if (next_field >= 'a' && next_field <= 'z') {
					current->colour = next_field;
				}
				x = next_x;
				y = next_y;
			}
		}
	}
	int x_pos() {
		return x;
	}
	int y_pos() {
		return y;
	}
	bool is_alive() {
		if (current) {
			return 1;
		}
		return 0;
	}
};

int main() {
	int x = 0, y = 0, x_max, y_max, edzio_size;
	char input_char, c;
	int input_num;

	cin >> x_max >> y_max >> edzio_size;
	Board *B = new Board(x_max, y_max);

	// populate board
	while ((x < x_max) || (y < y_max - 1)) {
		cin >> ws;
		c = cin.peek();
		input_num = 1;
		if ((c >= '0') && (c <= '9')) {
			cin >> input_num >> input_char;
		}
		else {
			cin >> input_char;
		}
		for (int i = 0; i < input_num; i++) {
			if (x < x_max) {
				B->poke(x++, y, input_char);
			}
			else {
				x = 0;
				B->poke(x++, ++y, input_char);
			}
		}
	}

	// move Edzio
	Edzio *E = new Edzio(edzio_size, x_max, y_max);

	while (cin && E->is_alive()) {
		cin >> ws;
		c = cin.peek();
		if (cin.eof()) break;
		if ((c >= '0') && (c <= '9')) {
			cin >> input_num >> input_char;
			for (int i = 0; i < input_num; i++) {
				E->move(input_char, B);
				if (! E->is_alive()) break;
			}
		}
		else {
			cin >> input_char;
			E->move(input_char, B);
		}
	}

	// game over
	if (!E->is_alive()) {
		cout << "Zegnaj, okrutny swiecie!\n";
	}
	cout << E->x_pos() << ' ' << E->y_pos() << '\n';
	for (y = 0; y < y_max; y++) {
		for (x = 0; x < x_max; x++) {
			cout << B->peek(x, y);
		}
		cout << '\n';
	}
	delete E;
	delete B;
}
