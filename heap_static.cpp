#include <iostream>

// initial dynamic array size
#define SIZE 4

using namespace std;
//typedef unsigned int uint;

class Heap {
private:
    int array[8192];
    int heap_size;
public:
    Heap() : heap_size(0) {}
    ~Heap() {}

    void heapify(int i) {
        int t, s;
        int left = i * 2;
        int right = i * 2 + 1;
        if (left <= heap_size && array[left] > array[i]) {
            t = left;
        }
        else {
            t = i;
        }
        if (right <= heap_size && array[right] > array[t]) {
            t = right;
        }
        if (t != i) {
            s = array[i];
            array[i] = array[t];
            array[t] = s;
            heapify(t);
        }
    }
    // '+'
    void push(int value) {
        heap_size++;
        int i = heap_size;
        int s;
        array[i] = value;
        while (i > 1 && array[i / 2] < array[i]) {
            s = array[i / 2];
            array[i / 2] = array[i];
            array[i] = s;
            i = i / 2;
        }
    }
    // '-'
    void pop() {
        if (heap_size) {
            cout << array[1] << '\n';
            array[1] = array[heap_size];
            heap_size--;
            for (int i = heap_size / 2; i > 0; i--) {
                heapify(i);
            }
        }
    }
    // 'r'
    void replace() {
        int i, value;
        cin >> heap_size;
        for (i = 1; i <= heap_size; i++) {
            cin >> value;
            array[i] = value;
        }
        for (i = heap_size / 2; i > 0; i--) {
            heapify(i);
        }
    }
    // 'p'
    void print() {
        if (heap_size) {
            for (int i = 1; i <= heap_size; i++) {
                cout << array[i] << ' ';
            }
            cout << '\n';
        }
    }
    // 'j'
    void join(int heap_no2, Heap *& H) {
        int new_heap_size = heap_size + H[heap_no2].heap_size;
        int i, j;
        for (i = heap_size + 1, j = 1; i <= new_heap_size; i++, j++) {
            array[i] = H[heap_no2].array[j];
        }
        heap_size = new_heap_size;
        H[heap_no2].heap_size = 0;
        for (i = new_heap_size / 2; i > 0; i--) {
            heapify(i);
        }
    }
};

int main() {
    char instr;
    int heap_no, heap_no2;
    int value;
    Heap* H = new Heap[10];

    while (1) {
        cin >> instr;
        switch (instr) {
        case '+':
            cin >> heap_no >> value;
            H[heap_no].push(value);
            break;
        case '-':
            cin >> heap_no;
            H[heap_no].pop();
            break;
        case 'p':
            cin >> heap_no;
            H[heap_no].print();
            break;
        case 'r':
            cin >> heap_no;
            H[heap_no].replace();
            break;
        case 'j':
            cin >> heap_no >> heap_no2;
            H[heap_no].join(heap_no2, H);
            break;
        case 'q':
            delete[] H;
            return 0;
        }
    }
}

// wykl. 4 str 25
