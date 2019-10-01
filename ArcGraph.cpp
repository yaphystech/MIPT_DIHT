//
// Created by yaspa on 03.03.2019.
//

#include "ArcGraph.h"

ArcGraph::ArcGraph(int numbOfVertices) {
    graph.reserve(numbOfVertices);
    amountOfVertices = numbOfVertices;
}

ArcGraph::ArcGraph(const IGraph *g) {
    int amount = g->VerticesCount();
    vector<int> nextvertices;
    for (int vertex = 0; vertex < amount; ++vertex) {
        g->GetNextVertices(vertex, nextvertices);
        for (int i = 0; i < nextvertices.size(); ++i) {
            AddEdge(vertex, nextvertices[i]);
        }
        nextvertices.clear();
    }
}

int ArcGraph::VerticesCount() const{
    return amountOfVertices;
}
void ArcGraph::AddEdge(int from, int to) {
    graph.emplace_back(from, to);
}
void ArcGraph::GetNextVertices(int vertex, vector<int> &vertices) const{
    for (int i = 0; i < amountOfVertices; ++i) {
        if (graph[i].first == vertex) {
            vertices.push_back(graph[i].second);
        }
    }
}
void ArcGraph::GetPrevVertices(int vertex, vector<int> &vertices) const{
    for (int i = 0; i < amountOfVertices; ++i) {
        if (graph[i].second == vertex) {
            vertices.push_back(graph[i].first);
        }
    }
}
