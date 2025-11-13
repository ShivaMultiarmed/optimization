#include<fstream>
#include<vector>
#include<string>

using namespace std;

const static u_int INF = 1e9;

void read(
    u_int& n,
    u_int& start,
    vector<vector<u_int>>& graph,
    vector<u_int>& distances
) {
    ifstream input("dijkstra.in");
    input >> n >> start;
    graph = vector(n, vector(n, INF));
    distances = vector(n, INF);
    for (u_int i = 0; i < n; i++) {
        for (u_int j = 0; j < n; j++) {
            string number;
            input >> number;
            try {
                graph.at(i).at(j) = stoi(number);
            } catch (invalid_argument e) {}
        }
    }
    input.close();
}

void write(const vector<u_int>& distances) {
    ofstream output("dijkstra.out");
    for (u_int distance : distances) {
        output << distance << " ";
    }
    output.close();
}

void solve(
    const u_int start,
    const vector<vector<u_int>>& graph,
    vector<u_int>& distances
) {
    u_int n = graph.size();
    vector<bool> visited(n, false);
    distances.at(start) = 0;
    for (u_int i = 0; i < n - 1; i++) {
        int u = -1;
        for (u_int j = 0; j < n; j++) {
            if (!visited.at(j) && (u == -1 || distances.at(j) < distances.at(u))) {
                u = j;
            }
        } 
        if (u == -1 || distances.at(u) == INF) {
            break;
        }
        visited[u] = true;
        for (u_int v = 0; v < n; v++) {
            if (graph.at(u).at(v) != INF && distances.at(u) != INF && distances.at(u) + graph.at(u).at(v) < distances.at(v)) {
                distances.at(v) = distances.at(u) + graph.at(u).at(v);
            }
        }
    }
}

int main () {
    u_int n, start;
    vector<u_int> distances;
    vector<vector<u_int>> graph;
    read(n, start, graph, distances);
    solve(start, graph, distances);
    write(distances);
    return 0;
}