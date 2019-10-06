#include <iostream>
#include "IGraph.h"
#include "SetGraph.h"
#include "ListGraph.h"
#include "ArcGraph.h"
#include "MatrixGraph.h"
#include <assert.h>

void AreOperationsDoingTheSame1() {
    vector<int> nextVertices1;
    vector<int> nextVertices2;
    vector<int> nextVertices3;
    vector<int> nextVertices4;
    vector<int> prevVertices1;
    vector<int> prevVertices2;
    vector<int> prevVertices3;
    vector<int> prevVertices4;
    int amountOfVertices = 4;
    int amountOfEdges = 3;
    ArcGraph arcGraph (amountOfVertices);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(1,2);
    arcGraph.AddEdge(2,3);
    SetGraph setGraph (&arcGraph);
    MatrixGraph matrixGraph (&arcGraph);
    ListGraph listGraph (&arcGraph);
    arcGraph.GetNextVertices(0, nextVertices1);
    setGraph.GetNextVertices(0, nextVertices2);
    matrixGraph.GetNextVertices(0, nextVertices3);
    listGraph.GetNextVertices(0, nextVertices4);
    arcGraph.GetPrevVertices(3, prevVertices1);
    setGraph.GetPrevVertices(3, prevVertices2);
    matrixGraph.GetPrevVertices(3, prevVertices3);
    listGraph.GetPrevVertices(3, prevVertices4);
    for (auto i : nextVertices1) {
        int flag = 0;
        for (auto j : nextVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices2) {
        int flag = 0;
        for (auto j : nextVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices3) {
        int flag = 0;
        for (auto j : nextVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices1) {
        int flag = 0;
        for (auto j : prevVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices2) {
        int flag = 0;
        for (auto j : prevVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices3) {
        int flag = 0;
        for (auto j : prevVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
}

void AreOperationsDoingTheSame() {
    vector<int> nextVertices1;
    vector<int> nextVertices2;
    vector<int> nextVertices3;
    vector<int> nextVertices4;
    vector<int> prevVertices1;
    vector<int> prevVertices2;
    vector<int> prevVertices3;
    vector<int> prevVertices4;
    int amountOfVertices = 5;
    int amountOfEdges = 4;
    ArcGraph arcGraph (amountOfVertices);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0,2);
    arcGraph.AddEdge(1,3);
    arcGraph.AddEdge(1, 2);
    arcGraph.AddEdge(3,4);
    SetGraph setGraph (&arcGraph);
    MatrixGraph matrixGraph (&arcGraph);
    ListGraph listGraph (&arcGraph);
    arcGraph.GetNextVertices(0, nextVertices1);
    setGraph.GetNextVertices(0, nextVertices2);
    matrixGraph.GetNextVertices(0, nextVertices3);
    listGraph.GetNextVertices(0, nextVertices4);
    arcGraph.GetPrevVertices(3, prevVertices1);
    setGraph.GetPrevVertices(3, prevVertices2);
    matrixGraph.GetPrevVertices(3, prevVertices3);
    listGraph.GetPrevVertices(3, prevVertices4);
    for (auto i : nextVertices1) {
        int flag = 0;
        for (auto j : nextVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices2) {
        int flag = 0;
        for (auto j : nextVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices3) {
        int flag = 0;
        for (auto j : nextVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices1) {
        int flag = 0;
        for (auto j : prevVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices2) {
        int flag = 0;
        for (auto j : prevVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices3) {
        int flag = 0;
        for (auto j : prevVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
}

void AreOperationsDoingTheSame3() {
    vector<int> nextVertices1;
    vector<int> nextVertices2;
    vector<int> nextVertices3;
    vector<int> nextVertices4;
    vector<int> prevVertices1;
    vector<int> prevVertices2;
    vector<int> prevVertices3;
    vector<int> prevVertices4;
    int amountOfVertices = 7;
    int amountOfEdges = 7;
    ArcGraph arcGraph (amountOfVertices);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 2);
    arcGraph.AddEdge(2, 6);
    arcGraph.AddEdge(3, 5);
    arcGraph.AddEdge(5, 4);
    SetGraph setGraph (&arcGraph);
    MatrixGraph matrixGraph (&arcGraph);
    ListGraph listGraph (&arcGraph);
    arcGraph.GetNextVertices(0, nextVertices1);
    setGraph.GetNextVertices(0, nextVertices2);
    matrixGraph.GetNextVertices(0, nextVertices3);
    listGraph.GetNextVertices(0, nextVertices4);
    arcGraph.GetPrevVertices(2, prevVertices1);
    setGraph.GetPrevVertices(2, prevVertices2);
    matrixGraph.GetPrevVertices(2, prevVertices3);
    listGraph.GetPrevVertices(2, prevVertices4);
    for (auto i : nextVertices1) {
        int flag = 0;
        for (auto j : nextVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices2) {
        int flag = 0;
        for (auto j : nextVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : nextVertices3) {
        int flag = 0;
        for (auto j : nextVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices1) {
        int flag = 0;
        for (auto j : prevVertices2) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices2) {
        int flag = 0;
        for (auto j : prevVertices3) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
    for (auto i : prevVertices3) {
        int flag = 0;
        for (auto j : prevVertices4) {
            if (i == j) {
                flag = 1;
                break;
            }
        }
        assert(flag ==1);
    }
}

int main() {
    AreOperationsDoingTheSame1();
    AreOperationsDoingTheSame2();
    AreOperationsDoingTheSame3();
    return 0;
}
