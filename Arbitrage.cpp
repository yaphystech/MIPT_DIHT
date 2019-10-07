#include <iostream>
#include <vector>
#include <set>

using std::vector, std::pair, std::set, std::cin, std::cout;

struct Edge{
    int from;
    int to;
    double cost;
    Edge(const int& from, const int& to, const double& cost): from(from), to(to), cost(cost) {};
};

class ArcGraph {
private:
    vector<Edge> adjacencyList;
    set<int> existentVertices;
public:
    ArcGraph() {}
    ~ArcGraph() {}
    void AddEdge(int& from, int& to, const double& cost);
    int VerticesCount() const;
    const vector<Edge>& GetAdjacencyList() const;
};

const vector<Edge>& ArcGraph::GetAdjacencyList() const{
    return adjacencyList;
}

int ArcGraph::VerticesCount() const {
    return existentVertices.size();
}

void ArcGraph::AddEdge(int& from, int& to, const double& cost) {
    existentVertices.insert(from);
    adjacencyList.push_back(Edge(from, to, cost));
}

bool FordBellman(const ArcGraph &graph) {
    int amountOfVertices = graph.VerticesCount();
    vector<double> distance(amountOfVertices, INT32_MIN);
    distance[0] = 1;
    vector<Edge> vec = graph.GetAdjacencyList();
    for(int i = 0; i < amountOfVertices; ++i) {
        for(auto edge : vec) {
            if (distance[edge.to] < distance[edge.from] * edge.cost) {
                distance[edge.to] = distance[edge.from] * edge.cost;
            }
        }
    }

    for(auto edge : vec) {
        if(distance[edge.to] < distance[edge.from] * edge.cost) {
            return true;
        }
    }
    return false;
}

int main() {
    int amountOfVertices;
    cin >> amountOfVertices;
    ArcGraph graph;
    for(int i = 0; i < amountOfVertices; ++i) {
        for (int j = 0; j < amountOfVertices; ++j) {
            double cost;
            if(i != j) {
                cin >> cost;
                if (cost != -1) {
                    graph.AddEdge(i, j, cost);
                }
            } else {
                graph.AddEdge(i, j, 1);
            }
        }
    }
    cout << ((FordBellman(graph)) ? "YES" : "NO");
    return 0;
}
