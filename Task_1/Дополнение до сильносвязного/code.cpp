#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
using std::max;

struct Graph {
    Graph(int vNumber) :
            vertexNumber(vNumber),
            g(vertexNumber),
            gr(vertexNumber),
            component_(vertexNumber, 0),
            used1(vertexNumber, false),
            used2(vertexNumber, false)
    {}

    int vertexNumber;
    vector<vector<int>> g;
    vector<int> component_;
    vector<vector<int>> gr;
    vector<char> used1;
    vector<char> used2;
    vector<int> order;
    vector<int> component;
};

void dfs1(int v, Graph& graph) {
    graph.used1[v] = true;
    for (size_t i = 0; i < graph.g[v].size(); ++i) {
        if (!graph.used1[graph.g[v][i]]) {
            dfs1(graph.g[v][i], graph);
        }
    }
    graph.order.push_back(v);
}

void dfs2(int v, Graph& graph) {
    graph.used2[v] = true;
    graph.component.push_back(v);
    for (size_t i = 0; i < graph.gr[v].size(); ++i) {
        if (!graph.used2[graph.gr[v][i]]) {
            dfs2(graph.gr[v][i], graph);
        }
    }
}
int findComponent(Graph& graph) {
    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (!graph.used1[i]) {
            dfs1(i, graph);
        }
    }
    int countComponent = 0;
    for (int i = 0; i < graph.vertexNumber; ++i) {
        int u = graph.order[graph.vertexNumber - 1 - i];
        if (!graph.used2[u]) {
            dfs2(u, graph);
            for (int t : graph.component) {
                graph.component_[t] = countComponent;
            }
            graph.component.clear();
            countComponent++;
        }
    }
    return countComponent;
}

int findMax(Graph& graph, int countComponent) {
    vector<bool> stok(countComponent, false);
    vector<bool> istok(countComponent, false);
    for (int i = 0; i < graph.vertexNumber; ++i) {
        int out = 0;
        int in = 0;
        for (int t : graph.g[i]) {
            if (graph.component_[i] != graph.component_[t]) {
                out++;
            }
        }
        for (int t : graph.gr[i]) {
            if (graph.component_[i] != graph.component_[t]) {
                in++;
            }
        }
        if (in != 0) {
            stok[graph.component_[i]] = true;
        }
        if (out != 0) {
            istok[graph.component_[i]] = true;
        }
    }
    int s = 0;
    int is = 0;
    for (int i = 0; i < countComponent; ++i) {
        if (stok[i] == false) {
            ++s;
        }
        if (istok[i] == false) {
            ++is;
        }
    }
    return max(s, is);
}


int main() {
    int v;
    cin >> v;
    int n;
    cin >> n;
    Graph graph(v);
    for (int i = 0; i < n; ++i) {
        int a = 0;
        int b = 0;
        cin >> a >> b;
        graph.g[a - 1].push_back(b - 1);
        graph.gr[b - 1].push_back(a - 1);
    }
    int countComponent = findComponent(graph);
    if (countComponent == 1) {
        cout << 0;
    }
    else {
        cout << findMax(graph, countComponent);
    }
    return 0;
}

