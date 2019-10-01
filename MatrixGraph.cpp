#include <iostream>
#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int numbOfVertices) {
    graph.resize(numbOfVertices);
    for (int i = 0; i < numbOfVertices; ++i) {
        graph[i].resize(numbOfVertices, -1);
    }
}

MatrixGraph::MatrixGraph(const IGraph *g) {
    graph.resize(g->VerticesCount());
    for (int i = 0; i < g->VerticesCount(); ++i) {
        graph[i].resize(g->VerticesCount(), -1);
        vector<int> nextVertices;
        g->GetNextVertices(i, nextVertices);
        for (int j = 0; j < nextVertices.size(); ++j) {
            AddEdge(i, nextVertices[j]); //добавляем все рёбра из графа g
        }
        nextVertices.clear();
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = 1; //означает, что между from и to есть ребро
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (int i = 0; i < graph[vertex].size(); ++i) {
        if (graph[vertex][i] == 1) {
            vertices.push_back(i);
        }
    }
}

void MatrixGraph::GetPrevVertices(int vertex, vector<int> &vertices) const {
    for (int i = 0; i < graph[vertex].size(); ++i) {
        if (graph[i][vertex] == 1) {
            vertices.push_back(i);
        }
    }
}

/*void MatrixGraph::Print() {
    for (int i = 0; i < graph.size(); ++i) {
        vector<int> nextVertices;
        GetNextVertices(i, nextVertices);
        std::cout << i <<"vertex" <<"   ";
        for (auto j : nextVertices) {
            cout << j <<'/';
        }
    }
}*/

int MatrixGraph::VerticesCount() const {
    return graph.size();
}
