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
            list(vertexNumber),
            reversed_list(vertexNumber),
            vertex_in_component(vertexNumber, 0),
            visited(vertexNumber, false),
            visited_reverse(vertexNumber, false)
    {}
    int vertexNumber;
    vector<vector<int>> list;
    vector<int> vertex_in_component;
    vector<vector<int>> reversed_list;
    vector<bool > visited;
    vector<bool> visited_reverse;
};

void DFS(int v, Graph& graph, vector<int>& leave) {
    graph.visited[v] = true;
    for (size_t i = 0; i < graph.list[v].size(); ++i) {
        if (!graph.visited[graph.list[v][i]]) {
            DFS(graph.list[v][i], graph, leave);
        }
    }
    leave.push_back(v);
}

void DFSReverse(int v, Graph& graph, vector<int>& component) {
    graph.visited_reverse[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < graph.reversed_list[v].size(); ++i) {
        if (!graph.visited_reverse[graph.reversed_list[v][i]]) {
            DFSReverse(graph.reversed_list[v][i], graph, component);
        }
    }

}

// Используем алгоритм Косарайю поиска сильносвязных компонент. Во вспомогательный вектор component
// в DFSReverse записали все вершины, входящие в ту же компоненту, в которую входит вершина i.
// В leave храним последовательность посещенных DFS'ом вершин.
// В vertex_in_component под номером вершины храним номер компоненты, которой эта вершина принадлежит.
int CountComponents(Graph& graph) {
    vector<int> leave;
    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (!graph.visited[i]) {
            DFS(i, graph, leave);
        }
    }
    int count = 0;
    for (int i = 0; i < graph.vertexNumber; ++i) {
        int v = leave[graph.vertexNumber - 1 - i];
        vector<int> component;
        if (!graph.visited_reverse[v]) {
            DFSReverse(v, graph, component);
            for (int t : component) {
                graph.vertex_in_component[t] = count;
            }
            component.clear();
            ++count;
        }
    }
    return count;
}

// stok[i] = true, если из i-ой компоненты не выходит ни одно ребро в другую, иначе stok[i] = false.
// istok[i] = true, если в i-ую компоненту не входит ни одно ребро из другой компоненты, иначе false.
// Подсчитываем кол-во "стоковых" и "истоковых" компонент. Минимальное кол-во рёбер, которые нужно
// добавить, чтобы граф стал сильносвязным, ровно столько, сколько нужно добавить, чтобы stok и istok
// содержали только false'ы. Т.е. чтобы из любой компоненты можно было попасть в другие и наоборот.
int MinAmountOfEdges(Graph& graph, int countComponent) {
    vector<bool> stok(countComponent, true);
    vector<bool> istok(countComponent, true);
    for (int i = 0; i < graph.vertexNumber; ++i) {
        for (int t : graph.list[i]) {
            if (graph.vertex_in_component[i] != graph.vertex_in_component[t]) {
                stok[graph.vertex_in_component[i]] = false;
                break;
            }
        }
        for (int t : graph.reversed_list[i]) {
            if (graph.vertex_in_component[i] != graph.vertex_in_component[t]) {
                istok[graph.vertex_in_component[i]] = false;
                break;
            }
        }
    }
    int s = 0;
    int is = 0;
    for (int i = 0; i < countComponent; ++i) {
        if (stok[i] == true) {
            ++s;
        }
        if (istok[i] == true) {
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
        graph.list[a - 1].push_back(b - 1);
        graph.reversed_list[b - 1].push_back(a - 1);
    }
    int countComponent = CountComponents(graph);
    if (countComponent == 1) {
        cout << 0;
    }
    else {
        cout << MinAmountOfEdges(graph, countComponent);
    }
    return 0;
}

