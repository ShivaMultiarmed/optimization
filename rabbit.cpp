#include<fstream>
#include<vector>
#include<iostream>

using namespace std;
/*
int choosePath(
	char* cells,
	vector<int>& memory,
	int pos
) {
	if (pos < 1 || pos > memory.size() - 1) return -1;
	if (cells[pos] == 'w') return -1;
	if (pos == 1) return 0;
	if (memory[pos] != -1) return memory[pos];
	int routeA = choosePath(cells, memory, pos - 1);
	int routeB = choosePath(cells, memory, pos - 3);
	int routeC = choosePath(cells, memory, pos - 5);
	int optimum = max(routeA, routeB);
	optimum = max(optimum, routeC);
	memory[pos] = optimum == -1 ? -1 : ((cells[pos] == '"' ? 1 : 0) + optimum);
	return memory[pos];
}

int main () {
	ifstream input("lepus.in");
	int n;
	input >> n;
	char* cells = new char[n + 1];
	cells[0] = '.';
	input >> (cells + 1);
	input.close();
	vector<int> memory(n + 1, -1);
	int max = choosePath(cells, memory, n);
	delete[] cells;
	ofstream output("lepus.out");
	output << max << endl;
	output.close();
	return 0;
} */

int main() {
    ifstream input("lepus.in");
    int n;
    input >> n;
    string cells;
    input >> cells;
    input.close();

    vector<int> dp(n + 1, -1);
    dp[0] = 0; 
    for (int i = 0; i < n; ++i) {
        if (cells[i] == 'w') continue;
        int best = -1;
        if (i - 1 >= 0 && dp[i - 1] != -1) best = max(best, dp[i - 1]);
        if (i - 3 >= 0 && dp[i - 3] != -1) best = max(best, dp[i - 3]);
        if (i - 5 >= 0 && dp[i - 5] != -1) best = max(best, dp[i - 5]);
        if (best != -1) dp[i] = best + (cells[i] == '"' ? 1 : 0);
    }

    int result = dp[n - 1]; 
    ofstream output("lepus.out");
    output << result << endl;
    output.close();
}
