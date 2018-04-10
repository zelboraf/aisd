#include <stdio.h>
#include <iostream>
using namespace std;

unsigned int getnum();

typedef struct tab {
	unsigned short int key;
	unsigned short int val;
} tab;

int main() {
	int i, n ,t;
	
	n = getnum();
	tab *in = new tab[n];
	tab *out = new tab[n];
	int *ctr = new int[n];

	for (i = 0; i < n; i++) {
		ctr[i] = 0;
		in[i].key = getnum();
		in[i].val = getnum();
	}
	for (i = 0; i < n; i++)
		ctr[in[i].key]++;
	for (i = 1; i < n; i++)
		ctr[i] += ctr[i - 1];
	for (i = n - 1; i >= 0; i--)
		out[ctr[in[i].key]-- -1] = in[i];

	t = getnum();
	if (t == 0)
		for (i = 0; i < n; i++)
			cout << out[i].key << endl;
	if (t == 1)	
		for (i = 0; i < n; i++)
			cout << out[i].key << ',' << out[i].val << endl;

	delete[] in;
	delete[] out;
	delete[] ctr;
	return 0;
}

unsigned int getnum() {
	int num = 0;
	char c;
	while(1) {
		c = getchar();
		if (c < '0' || c > '9')
			return num;
	       	num *= 10;
		num += c - '0';		
	}
}
