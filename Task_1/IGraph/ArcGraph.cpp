#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertex_count) : vec() {
    count = vertex_count;
}

ArcGraph::ArcGraph(const IGraph* graph) : ArcGraph(graph->VerticesCount()) {
    for (int i = 0; i < graph->VerticesCount(); ++i) {
        vector<int> next;
        graph->GetNextVertices(i, next);
        vec.push_back(next);
    }

}

void ArcGraph::AddEdge(int from, int to) {
    vector<int> pair;
    pair.push_back(from);
    pair.push_back(to);
    vec.push_back(pair);
}

int ArcGraph::VerticesCount() const {
    return count;
}

void ArcGraph::GetNextVertices(int vertex, vector<int>& vertices_) const {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i][0] == vertex) {
            vertices_.push_back(vec[i][1]);
        }
    }
}
void ArcGraph::GetPrevVertices(int vertex, vector<int>& vertices_) const {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i][1] == vertex) {
            vertices_.push_back(vec[i][0]);
        }
    }
}
