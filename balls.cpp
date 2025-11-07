#include<iostream>
#include<vector>

using namespace std;

int buildPyramid(int ballsCount) { // returns balls used
    int ballsUsed = 0, level = 0;
    do {
        ballsUsed += (level + 1) * (level + 2) / 2;
        level++;
    } while(ballsCount - ballsUsed >= (level + 1) * (level + 2) / 2);
    return ballsUsed;
}

int buildPyramids(int ballsCount) { // returns built pyramid count
    int ballsUsed = 0, pyramidsCount = 0;
    do {
        ballsUsed += buildPyramid(ballsCount - ballsUsed);
        pyramidsCount++;
    } while(ballsCount - ballsUsed > 0);
    return pyramidsCount;
}

int main () {
    int n;
    cin >> n;
    vector<int> testsCount(n);
    for (int i = 0; i < n; i++) {
        cin >> testsCount[i];
    }
    for (int i = 0; i < n; i++) {
        cout << buildPyramids(testsCount[i]) << endl;
    }
    return 0;
}