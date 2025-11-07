#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

int main () {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    long long a = 1, b = 1, c = 1;
    for (int i = 2; i <=n; i++) {
        long long newA = a + b + c, newB = b + c, newC = a + b + c;
        a = newA, b = newB, c = newC;
    }
    cout << a + b + c << endl;
    return 0;
}