#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

const static int INF = 1e8;

struct Edge {
    u_int start, end;
    int weight;
};

void read(
    u_int& n,
    vector<Edge>& graph,
    vector<u_int>& parents
) {
    ifstream input("kruskal.in");
    input >> n;
    for (u_int i = 0; i < n; i++) {
        for (u_int j = 0; j < n; j++) {
            string number;
            input >> number;
            try {
                if (i < j) {
                    graph.push_back({i, j, stoi(number)});
                }
            } catch (invalid_argument& e) {}
        }
    }
    input.close();
    parents.resize(n);
    for (u_int i = 0; i < parents.size(); i++) {
        parents[i] = i;
    }
}

void write(
    const u_int n,
    vector<Edge>& tree
) {
    ofstream output("kruskal.out");
    vector<vector<int>> graphMatrix(n, vector<int>(n, INF));
    for (u_int i = 0; i < n; i++) {
        graphMatrix[i][i] = 0;
    }
    for (const Edge edge : tree) {
        graphMatrix[edge.start][edge.end] = edge.weight;
        graphMatrix[edge.end][edge.start] = edge.weight;
    }
    for (u_int i = 0; i < n; i++) {
        for (u_int j = 0; j < n; j++) {
            output << (graphMatrix[i][j] < INF ? to_string(graphMatrix[i][j]) : "-") << " ";
        }
        output << endl;
    }
    output << endl;
    output.close();
}

u_int find (
    vector<u_int>& parents, 
    u_int x
) {
    return x == parents[x] ? x : parents[x] = find(parents, parents[x]);
}

void unite(
    vector<u_int>& parents,
    u_int x, 
    u_int y
) {
    x = find(parents, x);
    y = find(parents, y);
    if (x != y) {
        parents[x] = y;
    }
}

u_int solve(
    const u_int n,
    vector<Edge>& graph,
    vector<u_int>& parents,
    vector<Edge>& tree
) {
    u_int mst = 0, used = 0;
    sort(graph.begin(), graph.end(), [](const Edge& a, const Edge& b) -> bool { return a.weight < b.weight; });
    for (const Edge& edge : graph) {
        u_int xRoot = find(parents, edge.start);
        u_int yRoot = find(parents, edge.end);
        if (xRoot != yRoot) {
            unite(parents, edge.start, edge.end);
            mst += edge.weight;
            used++;
            tree.push_back(edge);
            if (used == n - 1) {
                break;
            }
        }
    }
    return mst;
}

int main (int argc, char** argv) {
    u_int n;
    vector<Edge> graph, tree;
    vector<u_int> parents;
    read(n, graph, parents);
    solve(n, graph, parents, tree);
    write(n, tree);
    return 0;
}