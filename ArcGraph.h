#pragma  once
#include "IGraph.h"

class ArcGraph: public IGraph {
private:
    vector<pair<int,int>> graph;
    int amountOfVertices;
public:
    ArcGraph(const IGraph* g);
    ArcGraph(int numbOfVertices);
    ~ArcGraph();
    int VerticesCount() const;
    void AddEdge(int from, int to);
    void GetNextVertices(int vertex, vector<int>& vertices) const;
    void GetPrevVertices(int vertex, vector<int>& vertices) const;
};
