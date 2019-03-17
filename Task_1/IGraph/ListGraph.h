#ifndef INC_1_LISTGRAPH_H
#define INC_1_LISTGRAPH_H

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int);
    ListGraph(const IGraph*);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<vector<int>> adjacencyList; // список смежности
};



#endif //INC_1_LISTGRAPH_H
