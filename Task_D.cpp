#include <iostream>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

class ListGraph{
private:
    vector<vector<int>> graph;
public:
    ListGraph(int numberOfVertices);
    int VerticesCount();
    void AddEdge(int from, int to);
    void GetNextVertices(int vertex, vector<int> &vertices);
};

ListGraph::ListGraph(int numberOfVertices) {
    graph.resize(numberOfVertices);
}

void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
}

int ListGraph::VerticesCount() {
    return graph.size();
}

void ListGraph::GetNextVertices(int vertex, vector<int> &vertices) {
    vertices = graph[vertex];
}

int BFS(ListGraph& graph, int from, int to) {
    vector<int> distance(graph.VerticesCount(), -1);
    queue<int> layer;
    int amountOfWays = 0;
    layer.push(from);
    distance[from] = 0;
    while (!layer.empty()) {
        int current = layer.front();
        layer.pop();
        vector<int> vertices;
        graph.GetNextVertices(current, vertices);
        for(int i = 0; i < vertices.size(); ++i) {
            if (distance[vertices[i]] == -1 || distance[vertices[i]] == distance[current] + 1) {
                if (vertices[i] != to) {
                    distance[vertices[i]] = distance[current] + 1;
                    layer.push(vertices[i]);
                    continue;
                } else {
                    layer.push(to);
                    if (distance[to] == -1) {
                        distance[to] = distance[current] + 1;
                        ++amountOfWays;
                        continue;
                    }
                    if (distance[to] == distance[current] + 1) {
                        ++amountOfWays;
                        continue;
                    }
                }
            }
        }
    }
    return amountOfWays;
}

int main() {
    int amountOfVertices = 0, amountOfEdges = 0;
    cin >> amountOfVertices;
    cin >> amountOfEdges;
    ListGraph graph(amountOfVertices);
    for (int i = 0; i < amountOfEdges; ++i){
        int from, to;
        cin >> from >> to;
        graph.AddEdge(from, to);
    }
    int from, to;
    cin >> from >> to;
    cout << BFS(graph, from, to);
    return 0;
}
