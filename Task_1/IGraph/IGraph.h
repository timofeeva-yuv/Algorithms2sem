#ifndef INC_1_IGRAPH_H
#define INC_1_IGRAPH_H

#include <iostream>
#include <vector>
using std::vector;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0; // подсчёт вершин
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};


#endif //INC_1_IGRAPH_H
