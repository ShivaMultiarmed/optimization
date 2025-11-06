#include <iostream>
#include <vector>

using namespace std;

int choosePath(vector<int>& ladder, u_int pos) {
    if (pos <= 0) return 0;
    if (pos == 1) return ladder.at(1);
    if (pos == 2) return ladder.at(2) + max(0, ladder.at(1));
    int routeA = choosePath(ladder, pos - 1);
    int routeB = choosePath(ladder, pos - 2);
    return ladder.at(pos) + max(routeA, routeB);
}

int main() {
    u_int n;
    cin >> n;
    vector<int> ladder = {0};
    for (u_int i = 1; i <= n; i++) {
        int value;
        cin >> value;
        ladder.push_back(value);
    }
    int result = choosePath(ladder, n);
    cout << result << endl;
    return 0;
}