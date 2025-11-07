#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int choosePath(vector<vector<int>>& field, int x, int y) {
	if (x < 0 || y > 7) return 1e9;
	if (x == 0 && y == 7) return field[7][0];
	int path1 = choosePath(field, x - 1, y);
	int path2 = choosePath(field, x, y + 1);
	int path3 = choosePath(field, x - 1, y + 1);
	return field[y][x] + min({path1, path2, path3});
}

int main() {
	vector<vector<int>> field(8, vector<int>(8));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> field[i][j];
		}
	}
	cout << choosePath(field, 7, 0) << endl;
	return 0;
}