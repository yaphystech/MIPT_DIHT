#include <iostream>
#include "IGraph.h"
#include "SetGraph.h"
#include "ListGraph.h"
#include "ArcGraph.h"
#include "MatrixGraph.h"

int main() {
    int amountOfVertices, amountOfEdges;
    cin >> amountOfVertices >> amountOfEdges;
    MatrixGraph graph (amountOfVertices);
    for (int i = 0; i < amountOfEdges; ++i) {
        int from, to;
        cin >> from >> to;
        graph.AddEdge(from, to);
    }
    graph.Print();
    return 0;
}
