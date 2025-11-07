#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int choosePath(int** field, int x, int y) {
	if (x < 0 || y > 7) return -1;
	if (x == 0 && y == 7) return field[7][0];
	int path1 = choosePath(field, x - 1, y);
	int path2 = choosePath(field, x, y + 1);
	int path3 = choosePath(field, x - 1, y + 1);
	vector<int> paths = {path1, path2, path3};
	vector<int> positivePaths;
	copy_if(paths.begin(), paths.end(), back_inserter(positivePaths),[](int n){return n >= 0;});
	if (positivePaths.size() == 0) return -1;
	else return field[y][x] + *(min_element(positivePaths.begin(), positivePaths.end()));
}

int main() {
	int field[8][8] = {
        {9, 9, 9, 9, 9, 9, 1, 9},
        {9, 9, 9, 9, 9, 1, 9, 2},
        {9, 9, 9, 9, 9, 9, 1, 9},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {0, 9, 9, 9, 9, 9, 9, 9}
    };
	cout << choosePath(field, 7, 0);
	return 0;
}