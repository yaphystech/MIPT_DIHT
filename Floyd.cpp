#include <iostream>
#include <vector>

using std::vector, std::pair, std::make_pair, std::cin, std::cout, std::endl, std::min;

class MatrixGraph {
private:
    vector<vector<int>> graph;
public:
    ~MatrixGraph() {};
    MatrixGraph(const int& amountOfVertices);
    void AddEdge(int& from, int& to, int& cost);
    int VerticesCount() const;
    void GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const;
    void Print() const;
    void ChangeCopyOfGraph(int &i, int &j, int &k); //изменяет копию графа. Можно сделать, чтобы
};

void MatrixGraph::ChangeCopyOfGraph(int &i, int &j, int &k) {
    graph[i][j] = min(graph[i][k] + graph[k][j], graph[i][j]);
}
//передаём граф именно по значению, т.к. не хотим менять его самого. Для этого есть копия.
MatrixGraph TransitiveClosure(MatrixGraph graph){ //возврат происходит по значению, так как копия создаётся внутри функции
    for(int k = 0; k < graph.VerticesCount(); ++k){ //и вернуть её по ссылке не получится
        for(int i = 0; i < graph.VerticesCount(); ++i){ 
            for(int j = 0; j < graph.VerticesCount(); ++j){
                graph.ChangeCopyOfGraph(i, j, k);
            }
        }
    }
    return graph;
}

MatrixGraph::MatrixGraph(const int& amountOfVertices){
    graph.resize(amountOfVertices);
    for(int i = 0; i < amountOfVertices; ++i){
        graph[i].assign(amountOfVertices, INT16_MAX);
    }
}

void MatrixGraph::AddEdge(int& from, int& to, int& cost){
    graph[from][to] = cost;
}

int MatrixGraph::VerticesCount() const{
    return graph.size();
}

void MatrixGraph::GetNextVertices(const int& vertex, vector<pair<int, int>>& vertices) const {
    vertices.clear();
    for(int i = 0; i < VerticesCount(); ++i){
        if(i != INT16_MAX){
            vertices.push_back(make_pair(i, graph[vertex][i]));
        }
    }
}

void MatrixGraph::Print() const{
    for(int i = 0; i < VerticesCount(); ++i) {
        for(int j = 0; j < VerticesCount(); ++j) {
            cout << ((graph[i][j] != INT16_MAX) ? graph[i][j] : 0) << ' ';
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
    TransitiveClosure(graph).Print();
    return 0;
}
