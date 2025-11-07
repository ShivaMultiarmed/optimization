#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main () {
    int N, P, p = 0;
    cin >> N;
    cin >> P;
    vector<int> boys;
    for (int i = 0; i < N; i++) {
        boys.push_back(i + 1);
    }
    do {
        p = (p + P - 1) % boys.size();
        boys.erase(boys.begin() + p);
    } while(boys.size() > 1);
    cout << boys[0] << endl;
    return 0;
}
