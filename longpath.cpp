/*#include<iostream>
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

 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> dp(n + 1, 0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            dp[v] = max(dp[v], dp[u] + 1);
            if (--indeg[v] == 0)
                q.push(v);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
