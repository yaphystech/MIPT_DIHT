#include <iostream>
#include <vector>

using std::vector, std::pair, std::make_pair, std::cin, std::cout, std::endl, std::min;

class MatrixGraph {
private:
    vector<vector<int>> adjacencyMatrix;
public:
    void TransitiveClosure();
    ~MatrixGraph() {};
    MatrixGraph(const int& amountOfVertices);
    void AddEdge(const int& from, const int& to, const int& cost);
    int VerticesCount() const;
    void GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const;
    void Print() const;
};

void MatrixGraph::TransitiveClosure(){
    auto& dist = adjacencyMatrix;
    for(int k = 0; k < VerticesCount(); ++k){
        for(int i = 0; i < VerticesCount(); ++i){
            for(int j = 0; j < VerticesCount(); ++j){
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }
}

MatrixGraph::MatrixGraph(const int& amountOfVertices){
    adjacencyMatrix.resize(amountOfVertices);
    for(int i = 0; i < amountOfVertices; ++i){
        adjacencyMatrix[i].assign(amountOfVertices, INT16_MAX);
    }
}

void MatrixGraph::AddEdge(const int& from, const int& to, const int& cost){
    adjacencyMatrix[from][to] = cost;
}

int MatrixGraph::VerticesCount() const{
    return adjacencyMatrix.size();
}

void MatrixGraph::GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const {
    vertices.clear();
    for(int i = 0; i < VerticesCount(); ++i){
        if(i != INT16_MAX){
            vertices.push_back(make_pair(i, adjacencyMatrix[vertex][i]));
        }
    }
}

void MatrixGraph::Print() const{
    for(int i = 0; i < VerticesCount(); ++i) {
        for(int j = 0; j < VerticesCount(); ++j) {
            cout << ((adjacencyMatrix[i][j] != INT16_MAX) ? adjacencyMatrix[i][j] : 0) << ' ';
        }
        cout << endl;
    }
}

int main() {
    int amountOfVertices;
    cin >> amountOfVertices;
    MatrixGraph graph(amountOfVertices);
    for(int i = 0; i < amountOfVertices; ++i) {
        for (int j = 0; j < amountOfVertices; ++j) {
            int cost;
            cin >> cost;
            graph.AddEdge(i, j, cost);
        }
    }
    graph.TransitiveClosure();
    graph.Print();
    return 0;
}
