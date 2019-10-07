#include <iostream>
#include "SetGraph.h"

SetGraph::SetGraph(int numbOfVertices) {
    graph.resize(numbOfVertices);
}

SetGraph::SetGraph(const IGraph *g) {
    graph.resize(g->VerticesCount());
    for (int i = 0; i < g->VerticesCount(); ++i) {
        vector<int> nextVertices;
        g->GetNextVertices(i, nextVertices);
        for (int j = 0; j < nextVertices.size(); ++j) {
            AddEdge(i, nextVertices[j]); //добавляем все рёбра из графа g
        }
        nextVertices.clear();
    }
}

void SetGraph::AddEdge(int from, int to) {
    graph[from].insert(to);
}

void SetGraph::GetNextVertices(int vertex, vector<int> &vertices) const{
    for (auto i : graph[vertex]) {
        vertices.push_back(i);
    }
}

void SetGraph::GetPrevVertices(int vertex, vector<int> &vertices) const{
    for (int i = 0; i < graph.size(); ++i) {
        for (auto j : graph[i]) {
            if (j == vertex) {
                vertices.push_back(i);
            }
        }
    }
}


int SetGraph::VerticesCount() const{
    return graph.size();
}
