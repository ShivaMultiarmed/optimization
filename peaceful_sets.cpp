#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }
    
    vector<vector<int>> dp(n + 1, vector<int>(n + 2, 0));
    
    for (int m = 1; m <= n + 1; m++) {
        dp[0][m] = 1;
    }
    
    for (int s = 1; s <= n; s++) {
        for (int m = n; m >= 1; m--) {
            int total = 0;
            for (int x = m; x <= s; x++) {
                int next_m = 2 * x;
                if (next_m > n) {
                    if (s - x == 0) {
                        total += 1;
                    }
                } else {
                    total += dp[s - x][next_m];
                }
            }
            dp[s][m] = total;
        }
    }
    
    cout << dp[n][1] << endl;
    
    return 0;
}