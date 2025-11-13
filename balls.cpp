// int buildPyramid(int ballsCount) {
//     int ballsUsed = 0, level = 0;
//     do {
//         ballsUsed += (level + 1) * (level + 2) / 2;
//         level++;
//     } while(ballsCount - ballsUsed >= (level + 1) * (level + 2) / 2);
//     return ballsUsed;
// }

// int buildPyramids(int ballsCount) {
//     int ballsUsed = 0, pyramidsCount = 0;
//     do {
//         ballsUsed += buildPyramid(ballsCount - ballsUsed);
//         pyramidsCount++;
//     } while(ballsCount - ballsUsed > 0);
//     return pyramidsCount;
// }

// int main () {
//     int n;
//     cin >> n;
//     vector<int> testsCount(n);
//     for (int i = 0; i < n; i++) {
//         cin >> testsCount[i];
//     }
//     for (int i = 0; i < n; i++) {
//         cout << buildPyramids(testsCount[i]) << endl;
//     }
//     return 0;
// }

#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = 1e9;

int buildPyramids(int ballsCount, vector<int>& tetra) {
    vector<int> pyramidsCount(ballsCount + 1, INF);
    pyramidsCount[0] = 0;
    for (int x = 1; x <= ballsCount; x++) {
        for (int t : tetra) {
            if (t > x) break;
            pyramidsCount[x] = min(pyramidsCount[x], pyramidsCount[x - t] + 1);
        }
    }
    return pyramidsCount[ballsCount];
}

int main () {
    int n;
    cin >> n;
    vector<int> ballCounts(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> ballCounts[i];
    }
    int maxBallCount = *max_element(ballCounts.begin(), ballCounts.end());
    vector<int> tetra;
    for (int h = 0; ; h++) {
        int size = h * (h + 1) * (h + 2) / 6;
        if (size > maxBallCount) break;
        tetra.push_back(size);
    }
    for (int ballsCount : ballCounts) {
        cout << buildPyramids(ballsCount, tetra) << endl;
    }
    return 0;
}