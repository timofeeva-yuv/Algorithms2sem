#ifndef INC_1_ARCGRAPH_H
#define INC_1_ARCGRAPH_H

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    ArcGraph (int vertex_count);
    void AddEdge(int, int);
    ArcGraph (const IGraph*);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<vector<int>> vec;
    int count;
};

#endif //INC_1_ARCGRAPH_H
