#pragma once

#include "IGraph.h"

class MatrixGraph : public IGraph{
private:
    vector<vector<int>> graph;
public:
    MatrixGraph(const IGraph* g);
    MatrixGraph(int numbOfVertices);
    ~MatrixGraph() {};
    int VerticesCount() const;
    void AddEdge(int from, int to);
    void GetNextVertices(int vertex, vector<int>& vertices) const;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;
    void Print ();
};
