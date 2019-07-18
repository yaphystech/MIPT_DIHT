#include <iostream>
#include <vector>

using std::vector, std::cin, std::cout;

enum Color{
    white,
    grey,
    black
};

class MatrixGraph{
private:
    vector<vector<short>> graph;
    vector<short> timeOfVisit;
    vector<Color> colors;

public:
    MatrixGraph(const short& numberOfVertices);
    int VerticesCount();
    void AddEdge(const short& from, const short& to);
    void GetNextVertices(const short& vertex, vector<short> &vertices, bool& flag);
    void BFS (const short& vertex, short parent, bool& flag, vector<short>& currentLayer, vector<short>& nextLayer);
};

MatrixGraph::MatrixGraph(const short& numberOfVertices) {
    graph.resize(numberOfVertices);
    timeOfVisit.assign(numberOfVertices, 0);
    colors.assign(numberOfVertices, white);
}

void MatrixGraph::AddEdge(const short& from, const short& to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
}

int MatrixGraph::VerticesCount() {
    return graph.size();
}

void MatrixGraph::GetNextVertices(const short& vertex, vector<short> &vertices, bool& flag) {
    for(short i = 0; i < graph[vertex].size(); ++i) {
        if (timeOfVisit[vertex] == timeOfVisit[graph[vertex][i]]) {
            flag = false;
            return;
        } else {
            if (colors[graph[vertex][i]] == white) {
                vertices.push_back(graph[vertex][i]);
                timeOfVisit[graph[vertex][i]] = timeOfVisit[vertex] + 1;
            }
        }
    }
}

void MatrixGraph::BFS(const short& vertex, short parent, bool& flag, vector<short>& currentLayer, vector<short>& nextLayer) {
    colors[vertex] = grey;
    if (parent == -1) {
        timeOfVisit[vertex] = 1;
        currentLayer.push_back(vertex);
    }
    for (short i = 0; i < currentLayer.size(); ++i) {
        GetNextVertices(currentLayer[i], nextLayer, flag);
    }
    if (!flag) {
        return;
    } else {
        currentLayer = nextLayer;
        nextLayer.clear();
        for (short i = 0; i < currentLayer.size(); ++i) {
            BFS(currentLayer[i], 1, flag, currentLayer, nextLayer);
        }
    }
}

int main(){
    short amountOfVertices = 0, amountOfEdges = 0;
    bool flag = true;
    vector<short> currentLayer;
    vector<short> nextLayer;
    cin >> amountOfVertices;
    cin >> amountOfEdges;
    MatrixGraph graph(amountOfVertices);
    for (short i = 0; i < amountOfEdges; ++i) {
        short from, to;
        cin >> from >> to;
        graph.AddEdge(from, to);
    }
    graph.BFS(0, -1, flag, currentLayer, nextLayer);
    if (flag){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return  0;
}
