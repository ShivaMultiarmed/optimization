#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>

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
        if (distances.at(v) >= INF) {
            continue;
        }
        for(int cur = v; cur != -1; cur = previousNodes.at(cur)) {
            paths.at(v).push_back(cur);
        }
        reverse(paths.at(v).begin(), paths.at(v).end());
    }
}

u_int randomNumber () {
    return rand() % (10 - 1) + 1;
}

void generate(
    u_int& n,
    u_int& start, 
    vector<vector<u_int>>& graph,
    vector<vector<u_int>>& paths,
    vector<u_int>& distances
) {
    fstream file("dijkstra.in", ios::in | ios::app);
    file >> n >> start;
    u_int m = sqrt(n);
    graph = vector(n, vector(n, INF));
    paths = vector(n, vector<u_int>());
    distances = vector(n, INF);
    for (u_int r = 0; r < m; r++) {
        for (u_int c = 0; c < m; c++) {
            u_int u = r * m + c;
            if (c < m - 1) {
                u_int v = r * m + c + 1;
                graph[u][v] = graph[v][u] = randomNumber();
            }
            if (r < m - 1) {
                u_int v = (r + 1) * m + c;
                graph[u][v] = graph[v][u] = randomNumber();
            }
        }
    }
    for (u_int i = 0; i < m * m; i++) {
        graph[i][i] = 0;
    }
    for (u_int i = 0; i < m * m; i++) {
        for (u_int j = 0; j < m * m; j++) {
            file << (graph[i][j] < INF ? to_string(graph[i][j]) : "-") << " ";
        }
        file << endl;
    }
    file.close();
}

vector<vector<pair<u_int, u_int>>> matrixToList (const vector<vector<u_int>>& matrix) {
    vector<vector<pair<u_int, u_int>>> list(matrix.size());
    for (u_int i = 0; i < matrix.size(); i++) {
        for (u_int j = 0; j < matrix.size(); j++) {
            if (0 < matrix[i][j] && matrix[i][j] < INF) {
                list[i].push_back({matrix[i][j], j});
            }
        }
    }
    return list;
}

void solveOnHeap(
    const u_int start,
    const vector<vector<pair<u_int, u_int>>>& graph,
    vector<vector<u_int>>& paths,
    vector<u_int>& distances
) {
    u_int n = graph.size();
    vector<int> previousNodes(n, -1);
    distances[start] = 0;
    priority_queue<pair<u_int, u_int>, vector<pair<u_int, u_int>>, greater<>> queue;
    queue.push({0, start});
    while(!queue.empty()) {
        auto [d, u] = queue.top();
        queue.pop();
        if (d > distances[u]) {
            continue;
        }
        for (auto [d, v] : graph[u]) {
            if (distances[u] + d < distances[v]) {
                distances[v] = distances[u] + d;
                previousNodes[v] = u;
                queue.push({distances[v], v});
            }
        }
    }
    u_int hasLongPath = 0;
    for (u_int v = 0; v < n; v++) {
        if (distances[v] >= INF) {
            hasLongPath++;
            continue;
        }
        for(int cur = v; cur != -1; cur = previousNodes[cur]) {
            paths[v].push_back(cur);
        }
        reverse(paths[v].begin(), paths[v].end());
    }
}

enum class Method {
    REGULAR, HEAP
};

enum class InputSource {
    FILE, GENERATION
};

int main (int argc, char** argv) {
    Method method = Method::REGULAR;
    InputSource input = InputSource::FILE;
    for (u_int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            method = Method::HEAP;
        } else if (string(argv[i]) == "-g") {
            input = InputSource::GENERATION;
        }
    }
    u_int n, start;
    vector<u_int> distances;
    vector<vector<u_int>> graph, paths;
    if (input == InputSource::FILE) {
        read(n, start, graph, paths, distances);
    } else {
        generate(n, start, graph, paths, distances);
    }
    if (method == Method::REGULAR) {
        solve(start, graph, paths, distances);
    } else {
        solveOnHeap(start, matrixToList(graph), paths, distances);
    }
    write(paths, distances);
    return 0;
}