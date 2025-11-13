#include <fstream>
#include<vector>

using namespace std;

int choosePath(
	int x,
	int y,
	vector<vector<int>>& memory
) {
	if (x < 0 || y < 0) return 0;
	if (x == 0 && y == 0) return 1;
	if (memory[y][x] != -1) return memory[y][x];
	int path1 = choosePath(x - 1, y - 2, memory);
	int path2 = choosePath(x - 2, y - 1, memory);
	memory[y][x] = path1 + path2;
	return memory[y][x];
}

int main () {
	int x, y, m, n;
	ifstream input("knight.in");
	input >> m;
	x = m - 1;
	input >> n;
	input.close();
	y = n - 1;
	ofstream output("knight.out");
	vector<vector<int>> memory(n, vector<int>(m, -1));
	output << choosePath(x, y, memory) << endl;
	output.close();
	return 0;
}