#include <iostream>

using namespace std;

int choosePath(int x, int y) {
	if (x < 0 || y < 0) return 0;
	if (x == 0 && y == 0) return 1;
	int path1 = choosePath(x - 1, y - 2);
	int path2 = choosePath(x - 2, y - 1);
	return path1 + path2;
}

int main () {
	int x, y, m, n;
	cin >> m;
	x = m - 1;
	cin >> n;
	y = n - 1;
	cout << choosePath(x, y) << endl;
	return 0;
}