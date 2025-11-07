#include<iostream>
#include<vector>

using namespace std;

struct Edge {
    int begin, end;
};

int main () {
    int nodeCount, edgeCount;
    cin >> nodeCount;
    cin >> edgeCount;
    vector<Edge> graph(edgeCount);
    for(int i = 0; i < edgeCount; i++) {
        cin >> graph[i].begin;
        cin >> graph[i].end;
    }
    return 0;
}