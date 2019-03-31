#include <iostream>
#include <queue>
#include <vector>
using std::queue;
using std::vector;
using std::cin;
using std::cout;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int);
    ListGraph(const IGraph*);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<vector<int>> adjacencyList;
};

ListGraph::ListGraph(int vertexCount) : adjacencyList(vertexCount) {}

ListGraph::ListGraph(const IGraph* graph) : ListGraph(graph->VerticesCount())
{
    for (int i = 0; i < graph->VerticesCount(); ++i) {
        vector <int> next;
        graph->GetNextVertices(i, next);
        adjacencyList.push_back(next);
    }
}

void ListGraph::AddEdge(int from, int to) {
    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyList.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    vertices = adjacencyList[vertex];
}

void ListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    for (int i = 0; i < adjacencyList.size(); ++i) {
        for (int second : adjacencyList[i]) {
            if (second == vertex) {
                vertices.push_back(i);
            }
        }
    }
}

bool BFS(IGraph* graph, int start) {
    queue<int> tops;
    vector<int> color(graph->VerticesCount());
    vector<int> set(graph->VerticesCount());
    color[start] = 1;
    set[start] = 1;
    tops.push(start);
    while ((!tops.empty())) {
        int vertex = tops.front();
        tops.pop();
        vector<int> next_vertices;
        graph->GetNextVertices(vertex, next_vertices);
        for (int i = 0; i < next_vertices.size(); ++i) {
            if (set[next_vertices[i]] == set[vertex]) {
                return false;
            }
            set[next_vertices[i]] = set[vertex] % 2 + 1;
            if (color[next_vertices[i]] == 0) {
                tops.push(next_vertices[i]);
                color[next_vertices[i]] = 1;
            }
        }
        color[vertex] = 2;
    }
    return true;
}

int main() {
    int N, M;
    cin >> N >> M;
    ListGraph graph(N);
    int from, to;
    for (int i = 0; i < M; ++i) {
        cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }
    if (BFS(&graph, 0)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
