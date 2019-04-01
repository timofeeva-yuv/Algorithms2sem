#include <iostream>
#include <vector>
#include <set>
using std::vector;
using std::pair;
using std::make_pair;
using std::cin;

const int MAX = 1000000000;

struct Graph {
    Graph(int n): countVertex(n), dist(n), short_path_to(n, MAX) {}
    int countVertex;
    vector<vector<pair<int, int>>> dist;
    vector<int> short_path_to;
};

void Dijkstra(int s, Graph& graph) { // кратчайшие пути  из вершины s
    graph.short_path_to[s] = 0;
    std::set <pair<int, int>> q;
    q.insert(make_pair(graph.short_path_to[s], s));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (size_t j = 0; j < graph.dist[v].size(); ++j) {
            int to = graph.dist[v][j].first;
            int len = graph.dist[v][j].second;
            if (graph.short_path_to[v] + len < graph.short_path_to[to]) {
                q.erase(make_pair(graph.short_path_to[to], to));
                graph.short_path_to[to] = graph.short_path_to[v] + len;
                q.insert(make_pair(graph.short_path_to[to], to));
            }
        }
    }
}



int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        graph.dist[a].push_back(make_pair(b, c));
        graph.dist[b].push_back(make_pair(a, c));
    }
    int start = 0, end = 0;
    cin >> start >> end;
    Dijkstra(start, graph); // для вершины start находим кратчайшие пути до всех вершин
    std::cout << graph.short_path_to[end];
    return 0;
}

