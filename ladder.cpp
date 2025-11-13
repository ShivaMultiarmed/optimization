#include <vector>
#include <fstream>

using namespace std;

int choosePath(
    vector<int>& ladder,
    vector<int>& memory,
    int pos
) {
    if (memory.at(pos) != NULL) return memory.at(pos);
    int result;
    if (pos <= 0) result = 0;
    else if (pos == 1) result = ladder.at(1);
    else if (pos == 2) result = ladder.at(2) + max(0, ladder.at(1));
    else {
        int routeA = choosePath(ladder, memory, pos - 1);
        int routeB = choosePath(ladder, memory, pos - 2);
        result = ladder.at(pos) + max(routeA, routeB);
    }
    memory.at(pos) = result;
    return result;
}

int main() {
    ifstream input("ladder.in");
    int n;
    input >> n;
    vector<int> ladder = {0}, memory(n + 1, NULL);
    for (int i = 1; i <= n; i++) {
        int value;
        input >> value;
        ladder.push_back(value);
    }
    input.close();
    int result = choosePath(ladder, memory, n);
    ofstream output("ladder.out");
    output << result << endl;
    output.close();
    return 0;
}