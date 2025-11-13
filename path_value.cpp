#include <fstream>
#include <vector>

using namespace std;

int choosePath(
	vector<vector<int>>& field,
	vector<vector<int>>& memory,
	int x,
	int y
) {
	if (x < 0 || y > 7) return 1e9;
	if (x == 0 && y == 7) return field[7][0];
	if (memory[y][x] != -1) return memory[y][x];
	int path1 = choosePath(field, memory, x - 1, y);
	int path2 = choosePath(field, memory, x, y + 1);
	int path3 = choosePath(field, memory, x - 1, y + 1);
	int minimum = min(path1, path2);
	minimum = min(minimum, path3);
	memory[y][x] = field[y][x] + minimum;
	return memory[y][x];
}

int main() {
	vector<vector<int>> field(8, vector<int>(8)), memory(8, vector<int>(8));
	ifstream input("king2.in");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			input >> field[i][j];
			memory[i][j] = -1;
		}
	}
	input.close();
	ofstream output("king2.out");
	output << choosePath(field, memory, 7, 0) << endl;
	output.close();
	return 0;
}