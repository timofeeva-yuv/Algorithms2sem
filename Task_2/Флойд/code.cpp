#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cin;
using std::cout;

void Floyd(vector<vector<int>>& graph) {
    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    return;
}


int main() {
    int n = 0;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = 0;
            cin >> x;
            graph[i].push_back(x);
        }
    }
    Floyd(graph);
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            cout << graph[i][j] << ' ';
        }
        cout << "\n";
    }
    return 0;
}

