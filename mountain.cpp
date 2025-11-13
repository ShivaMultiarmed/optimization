#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

const int INF = 10000000;

int choosePath(
    vector<vector<int>>& mountain,
    vector<vector<int>>& memory,
    int level,
    int cell
) {
    if (cell < 0 || level < 0 || cell > level) return -INF;
    if (level == 0) {
        if (cell == 0) return mountain[0][0];
        else return -INF;
    }
    if (memory[level][cell] != -INF) return memory[level][cell];
    int result;
    if (cell == 0) result = mountain[level][cell] + choosePath(mountain, memory, level - 1, cell);
    else if (cell == level) result = mountain[level][cell] + choosePath(mountain, memory, level - 1, cell - 1);
    else {
        int path1 = choosePath(mountain, memory, level - 1, cell - 1);
        int path2 = choosePath(mountain, memory, level - 1, cell);
        result = mountain[level][cell] + max(path1, path2);
    }
    memory[level][cell] = result;
    return result;
}

int main () {
    int n;
    cin >> n;
    vector<vector<int>> mountain(n), memory(n);
    for (int i = 0; i < n; i++) {
        mountain[i].resize(i + 1);
        memory[i].resize(i + 1, -INF);
        for (int j = 0; j < i + 1; j++) {
            cin >> mountain[i][j];
        }
    }
    int maximum = -INF;
    for (int i = 0; i < n; i++) {
        maximum = max(maximum, choosePath(mountain, memory, n - 1, i));
    }
    cout << maximum << endl;
    return 0;
}