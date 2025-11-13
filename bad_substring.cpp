#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long A[23] = {0}, B[23] = {0}, C[23] = {0};
    
    if (n >= 1) {
        A[1] = B[1] = C[1] = 1;
        for (int i = 2; i <= n; i++) {
            A[i] = A[i-1] + B[i-1] + C[i-1];
            B[i] = B[i-1] + C[i-1];
            C[i] = A[i-1] + B[i-1] + C[i-1];
        }
    }

    long long result = (n == 0) ? 1 : A[n]+B[n]+C[n];
    cout << result << endl;
    return 0;
}
