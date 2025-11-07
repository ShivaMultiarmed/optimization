#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

int choosePath(vector<vector<int>>& mountain, int level, int cell) {
    if (level == 0) return mountain[0][0];
    if (cell == 0) return mountain[level][cell] + choosePath(mountain, level - 1, cell);
    if (cell == level) return mountain[level][cell] + choosePath(mountain, level - 1, cell - 1);
    int path1 = choosePath(mountain, level - 1, cell - 1);
    int path2 = choosePath(mountain, level - 1, cell);
    return mountain[level][cell] + max(path1, path2);
}

int main () {
    int n = 4;
    //cin >> n;
    vector<vector<int>> mountain = {
        {1},
        {4, 3},
        {5, 6, 7},
        {8, 9, 0, 9}
    };
    /*(n);
    for (int i = 0; i < n; i++) {
        mountain[i].resize(i + 1);
        for (int j = 0; j < i + 1; j++) {
            cin >> mountain[i][j];
        }
    }*/
    vector<int> possibleResults(n);
    for (int i = 0; i < n; i++) {
        possibleResults[i] = choosePath(mountain, n - 1, i);
    }
    cout << *max_element(possibleResults.begin(), possibleResults.end()) << endl;
    return 0;
}