#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

const static u_int INF = 1e9;

void read(
    u_int& n,
    u_int& start,
    vector<vector<u_int>>& graph,
    vector<vector<u_int>>& paths,
    vector<u_int>& distances
) {
    ifstream input("dijkstra.in");
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
    const vector<vector<u_int>>& paths,
    const vector<u_int>& distances
) {
    ofstream output("dijkstra.out");
    for (u_int v = 0; v < paths.size(); v++) {
        output << v << ": ";
        for (u_int cur = 0; cur < paths.at(v).size(); cur++) {
            output << paths.at(v).at(cur) << " ";
            if (cur < paths.at(v).size() - 1) {
                output << "-> ";
            }
        }
        output << "(" << distances.at(v) << ")" << endl;
    }
    output.close();
}

void solve(
    const u_int start,
    const vector<vector<u_int>>& graph,
    vector<vector<u_int>>& paths,
    vector<u_int>& distances
) {
    u_int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> previousNodes(n, -1);
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
                previousNodes.at(v) = u;
            }
        }
    }
    for (u_int v = 0; v < n; v++) {
        if (distances.at(v) == INF) {
            continue;
        }
        for(int cur = v; cur != -1; cur = previousNodes.at(cur)) {
            paths.at(v).push_back(cur);
        }
        reverse(paths.at(v).begin(), paths.at(v).end());
    }
}

void solveOnHeap(
    const u_int start,
    const vector<vector<u_int>>& graph,
    vector<vector<u_int>>& paths,
    vector<u_int>& distances
) {
    u_int n = graph.size();
    vector<int> previousNodes(n, -1);
    distances.at(start) = 0;
    priority_queue<pair<u_int, u_int>, vector<pair<u_int, u_int>>, greater<>> queue;
    queue.push({0, start});
    while(!queue.empty()) {
        auto [d, u] = queue.top();
        queue.pop();
        if (d > distances.at(u)) {
            continue;
        }
        for (u_int v = 0; v < n; v++) {
            if (graph.at(u).at(v) != INF && distances.at(u) + graph.at(u).at(v) < distances.at(v)) {
                distances.at(v) = distances.at(u) + graph.at(u).at(v);
                previousNodes.at(v) = u;
                queue.push({distances.at(v), v});
            }
        }
    }
    for (u_int v = 0; v < n; v++) {
        if (distances.at(v) == INF) {
            continue;
        }
        for(int cur = v; cur != -1; cur = previousNodes.at(cur)) {
            paths.at(v).push_back(cur);
        }
        reverse(paths.at(v).begin(), paths.at(v).end());
    }
}

enum class Method {
    REGULAR, HEAP
};

int main (int argc, char** argv) {
    Method method = Method::REGULAR;
    if (argv[1] == "-h") {
        method = Method::HEAP;
    }
    u_int n, start;
    vector<u_int> distances;
    vector<vector<u_int>> graph, paths;
    read(n, start, graph, paths, distances);
    solve(start, graph, paths, distances);
    write(paths, distances);
    return 0;
}