#ifndef INC_1_MATRIXGRAPH_H
#define INC_1_MATRIXGRAPH_H

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int);
    MatrixGraph(const IGraph*);
    void AddEdge(int, int);
    int VerticesCount() const;
    void GetNextVertices(int, vector<int>&) const;
    void GetPrevVertices(int, vector<int>&) const;
private:
    vector<vector<bool>> adjacencyMatrix; // матрица смежности
};

#endif //INC_1_MATRIXGRAPH_H