#include <iostream>
#include <vector>
#include <queue>

using std::vector, std::queue, std::cin, std::cout;

class ListGraph {
private:
    vector<vector<int>> graph;
public:
    ListGraph(const int& numbOfVertices);
    void AddEdge(const int& from, const int& to);
    int VerticesCount() const;
    void GetNextVertices(const int& vertex, vector<int>& vertices) const;
};

ListGraph::ListGraph(const int& numbOfVertices) {
    graph.resize(numbOfVertices);
}

void ListGraph::AddEdge(const int& from, const int& to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return graph.size();
}

void ListGraph::GetNextVertices(const int& vertex, vector<int>& vertices) const {
    vertices = graph[vertex];
}

struct State {
    State() = default;
    State (const int& d, const int& p);
    int depth = 0;
    int paths = 0;
};

State::State (const int& d, const int& p) {
    depth = d;
    paths = p;
}

int NumbersOfWays(const ListGraph& myGraph, int& start, int& end) {
    queue<int> bfsQueue; //стандартная очередь для BFS
    bfsQueue.push(start);
    vector<State> states(myGraph.VerticesCount(), State()); //хранит минимальную глубину и количество путей в i
    states[start].depth = 1;
    states[start].paths = 1;
    while (!bfsQueue.empty()) {
        int cur = bfsQueue.front();
        bfsQueue.pop();
        vector<int> vertices;
        myGraph.GetNextVertices(cur, vertices);
        for (int i : vertices) {
            if (states[i].depth == 0) {
                states[i] = State(states[cur].depth + 1, states[cur].paths); bfsQueue.push(i);
            }
            else if (states[i].depth == states[cur].depth + 1) {
                states[i].paths += states[cur].paths;
            }
        }
    }
    return states[end].paths;
}

int main() {
    int amountOfVertices, amountOfEdges;
    cin >> amountOfVertices >> amountOfEdges;
    ListGraph graph(amountOfVertices);
    for (int i = 0; i < amountOfEdges; ++i) {
        int from, to;
        cin >> from >> to;
        graph.AddEdge(from, to);
    }
    int v, w;
    cin >> v >> w;
    cout << NumbersOfWays(graph, v, w);
    return 0;
}
