#include <iterator>
#include <vector>
#include "ListGraph.h"

ListGraph::ListGraph(int numberOfVertices) {
    graph.resize(numberOfVertices);
}

ListGraph::ListGraph(const IGraph *g) {
    graph.resize(g->VerticesCount());
    for (int i = 0; i < graph.size(); ++i) {
        g->GetNextVertices(i, graph[i]);
    }
}

void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const{
    return graph.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int> &vertices) const{
    for (int i = 0; i < graph[vertex].size(); ++i) {
        vertices.push_back(graph[vertex][i]);
    }
}

void ListGraph::GetPrevVertices(int vertex, vector<int> &vertices) const{
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            if (graph[i][j] == vertex) {
                vertices.push_back(i);
            }
        }
    }
}
