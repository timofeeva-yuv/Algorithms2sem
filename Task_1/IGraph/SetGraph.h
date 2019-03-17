#ifndef INC_1_SETGRAPH_H
#define INC_1_SETGRAPH_H

#include "IGraph.h"
#include <unordered_set>

class SetGraph : public IGraph {
public:
    SetGraph(int);
    SetGraph(const IGraph*);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const;
private:
    vector<std::unordered_set<int>> graph;
    //std::vector< std::vector<int> > graph;
};

#endif //INC_1_SETGRAPH_H
