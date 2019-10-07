#pragma  once

#include <list>
#include "IGraph.h"

class ListGraph : public IGraph {
private:
    vector<vector<int>> graph;
public:
    ListGraph(const IGraph * g);
    ListGraph(int numberOfVertices);
    ~ListGraph() {};
    int VerticesCount() const;
    void AddEdge(int from, int to);
    void GetNextVertices(int vertex, vector<int> &vertices) const;
    void GetPrevVertices(int vertex, vector<int> &vertices) const;
};
