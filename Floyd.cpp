#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;
using std::cin;
using std::cout;
using std::endl;

class Matrixgraph {
public:
    void transitive_closure();
    ~Matrixgraph() {};
    Matrixgraph(const int& amount_of_vertices);
    void AddEdge(const int& from, const int& to, const int& cost);
    int VerticesCount() const;
    void GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const;
    void print();
private:
    vector<vector<int>> adjacency_matrix;
};

void Matrixgraph::transitive_closure(){
    auto& dist = adjacency_matrix;
    for(int k = 0; k < VerticesCount(); ++k){
        for(int i = 0; i < VerticesCount(); ++i){
            for(int j = 0; j < VerticesCount(); ++j){
                dist[i][j] = std::min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }
}

Matrixgraph::Matrixgraph(const int& amount_of_vertices){
    adjacency_matrix.resize(amount_of_vertices);
    for(int i = 0; i < amount_of_vertices; ++i){
        adjacency_matrix[i].assign(amount_of_vertices, INT16_MAX);
    }
}

void Matrixgraph::AddEdge(const int& from, const int& to, const int& cost){
    adjacency_matrix[from][to] = cost;
}

int Matrixgraph::VerticesCount() const{
    return adjacency_matrix.size();
}

void Matrixgraph::GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const {
    vertices.clear();
    for(int i = 0; i < VerticesCount(); ++i){
        if(i != INT16_MAX){
            vertices.push_back(make_pair(i, adjacency_matrix[vertex][i]));
        }
    }
}

void Matrixgraph::print(){
    for(int i = 0; i < VerticesCount(); ++i) {
        for(int j = 0; j < VerticesCount(); ++j) {
            cout << ((adjacency_matrix[i][j] != INT16_MAX) ? adjacency_matrix[i][j] : 0) << ' ';
        }
        cout << endl;
    }
}

int main() {
    int amount_of_vertices;
    cin >> amount_of_vertices;
    Matrixgraph graph(amount_of_vertices);
    for(int i = 0; i < amount_of_vertices; ++i) {
        for (int j = 0; j < amount_of_vertices; ++j) {
            int cost;
            cin >> cost;
            graph.AddEdge(i, j, cost);
        }
    }
    graph.transitive_closure();
    graph.print();
    return 0;
}
