#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::pair;

class Arcgraph {
public:
    Arcgraph() {}
    ~Arcgraph() {}
    void AddEdge(const int& from, const int& to, const double& cost);
    int VerticesCount() const;
    friend bool ford_bellman(const Arcgraph& graph);
private:
    struct Edge{
        int from;
        int to;
        double cost;
        Edge(const int& from_, const int& to_, const double& cost_):
            from(from_), to(to_), cost(cost_) {}
    };
    std::vector<Edge> adjacency_list;
    std::set<int> existent_vertices;
};

int Arcgraph::VerticesCount() const {
    return existent_vertices.size();
}

void Arcgraph::AddEdge(const int& from, const int& to, const double& cost) {
    existent_vertices.insert(from);
    adjacency_list.push_back(Edge(from, to, cost));
}

bool ford_bellman(const Arcgraph& graph) {
    int amount_of_vertices = graph.VerticesCount();
    vector<double> distance(amount_of_vertices, INT32_MIN);
    distance[0] = 1;
    for(int it = 0; it < amount_of_vertices; ++it) {
        for(auto edge : graph.adjacency_list) {
            if (distance[edge.to] < distance[edge.from] * edge.cost) {
                distance[edge.to] = distance[edge.from] * edge.cost;
            }
        }
    }

    for(auto edge : graph.adjacency_list) {
        if(distance[edge.to] < distance[edge.from] * edge.cost) {
            return true;
        }
    }
    return false;
}

int main() {
    int amount_of_vertices;
    std::cin >> amount_of_vertices;
    Arcgraph graph;
    for(int i = 0; i < amount_of_vertices; ++i) {
        for (int j = 0; j < amount_of_vertices; ++j) {
            double cost;
            if(i != j) {
                std::cin >> cost;
                graph.AddEdge(i, j, cost);
            } else {
                graph.AddEdge(i, j, 1);
            }
        }

    }
    std:: cout << ((ford_bellman(graph)) ? "YES" : "NO");
    return 0;
}
