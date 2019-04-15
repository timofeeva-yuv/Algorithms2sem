#include <vector>
#include <iostream>
using std::vector;
using std::cin;
using std::cout;

void ford_bellman(vector<vector<double>>& graph, vector<double>& d) {
    for (int j = 0; j < graph.size() - 1; ++j) {
        for (int v = 0; v < graph.size(); ++v) {
            for (int t = 0; t < graph.size(); ++t) {
                if (graph[t][v] != -1) {
                    if (d[t] != -1 && d[v] < d[t] * graph[t][v]) {
                        d[v] = d[t] * graph[t][v];
                    }
                }
            }
        }
    }
}

bool arbitrage(vector<vector<double>>& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        vector<double> d(graph.size(), -1); //массив расстояний
        d[i] = 1;
        ford_bellman(graph, d);
        for (int v = 0; v < graph.size(); ++v) {
            for (int i = 0; i < graph.size(); ++i) {
                if (graph[i][v] != -1) {
                    if (d[i] != -1 && d[v] < d[i] * graph[i][v]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int n = 0;
    cin >> n;
    vector<vector<double>> graph(n, vector<double>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double x = 0;
                cin >> x;
                graph[i][j] = x;
            }
        }
    }
    if (arbitrage(graph)) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}
