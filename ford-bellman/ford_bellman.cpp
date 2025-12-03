#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

const static int INF = 1e8;

void read(
    u_int& n,
    u_int& start,
    vector<vector<int>>& graph,
    vector<vector<u_int>>& paths,
    vector<int>& distances
) {
    ifstream input("ford_bellman.in");
    input >> n >> start;
    graph = vector(n, vector(n, INF));
    paths = vector(n, vector<u_int>());
    distances = vector(n, INF);
    for (u_int i = 0; i < n; i++) {
        for (u_int j = 0; j < n; j++) {
            string number;
            input >> number;
            try {
                graph.at(i).at(j) = stoi(number);
            } catch (invalid_argument& e) {}
        }
    }
    input.close();
}

void write(
    const u_int start,
    const vector<vector<u_int>>& paths,
    const vector<int>& distances
) {
    ofstream output("ford_bellman.out");
    for (u_int v = 0; v < paths.size(); v++) {
        output << v << ": ";
        if (paths[v][0] == start) {
            for (u_int cur = 0; cur < paths.at(v).size(); cur++) {
                output << paths.at(v).at(cur) << " ";
                if (cur < paths.at(v).size() - 1) {
                    output << "-> ";
                }
            }
            output << "(" << distances.at(v) << ")" << endl;
        } else {
            output << "(-∞)" << endl;
        }
    }
    output.close();
}

void solve(
    const u_int start,
    const vector<vector<int>>& graph,
    vector<vector<u_int>>& paths,
    vector<int>& distances
) {
    u_int n = graph.size();
    vector<int> previousNodes(n, -1);
    distances.at(start) = 0;
    
    for (u_int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (u_int u = 0; u < n; u++) {
            if (distances[u] == INF) {
                continue;
            }
            for (u_int v = 0; v < n; v++) {
                if (graph[u][v] != INF && distances[u] + graph[u][v] < distances[v]) {
                    distances[v] = distances[u] + graph[u][v];
                    previousNodes.at(v) = u;
                    updated = true;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    for (u_int v = 0; v < n; v++) {
        if (distances.at(v) == INF) {
            continue;
        }
        for(int cur = v; cur != -1 && find(paths[v].begin(), paths[v].end(), cur) == paths[v].end(); cur = previousNodes.at(cur)) {
            paths.at(v).push_back(cur);
        }
        reverse(paths.at(v).begin(), paths.at(v).end());
    }
}

int main (int argc, char** argv) {
    u_int n, start;
    vector<int> distances;
    vector<vector<int>> graph;
    vector<vector<u_int>> paths;
    read(n, start, graph, paths, distances);
    solve(start, graph, paths, distances);
    write(start, paths, distances);
    return 0;
}