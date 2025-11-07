#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

void dfs(
    int v,
    const vector<vector<int>>& graph,
    vector<bool>& visited,
    stack<int>& topo
) {
    visited[v] = true;
    for (int u = 0; u < graph.size(); u++) {
        if (graph[v][u] && !visited[u]) {
            dfs(u, graph, visited, topo);
        }
    }
    topo.push(v);
}

int main () {
    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;
    vector<vector<int>> graph(nodeCount, vector<int>(nodeCount, 0));
    for(int i = 0; i < edgeCount; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        graph[x][y] = 1;
    }
    vector<bool> visited(nodeCount, false);
    stack<int> topology;
    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, topology);
        }
    }
    vector<int> longestPaths(nodeCount, 0);
    while(!topology.empty()) {
        int v = topology.top();
        topology.pop();
        for (int u = 0; u < nodeCount; u++) {
            if (graph[v][u]) {
                longestPaths[u] = max(longestPaths[u], longestPaths[v] + 1);
            }
        }
    }
    int longestPath = *(max_element(longestPaths.begin(), longestPaths.end()));
    cout << longestPath << endl;
    return 0;
}