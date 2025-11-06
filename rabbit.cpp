#include <iostream>
#include <algorithm>

using namespace std;

int choosePath(char* cells, int pos) {
	if (pos < 1) return -1;
	if (cells[pos] == 'w') return -1;
	if (pos == 1) return 0;
	int routeA = choosePath(cells, pos - 1);
	int routeB = choosePath(cells, pos - 3);
	int routeC = choosePath(cells, pos - 5);
	int optimum = max({routeA, routeB, routeC});
	if (optimum == -1) return -1;
	return (cells[pos] == '"' ? 1 : 0) + optimum;
}

int main () {
	int n;
	cin >> n;
	char* cells = new char[n + 1];
	cells[0] = '.';
	cin >> (cells + 1);
	int max = choosePath(cells, n);
	cout << max << endl;
	delete[] cells;
	return 0;
}