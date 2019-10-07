#pragma  once

#include "IGraph.h"
#include <unordered_set>

class SetGraph : public IGraph {
private:
    vector<unordered_set<int>> graph;
public:
    SetGraph(const IGraph* g);
    SetGraph(int numbOfVertices);
    ~SetGraph() {};
    int VerticesCount() const;
    void AddEdge(int from, int to);
    void GetNextVertices(int vertex, vector<int>& vertices) const;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;
};
