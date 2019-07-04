#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

class Listgraph {
public:
    Listgraph(const int amount_of_vertices) {
        adjacency_list.resize(amount_of_vertices);
    }
    ~Listgraph() {}

    void AddEdge(int from, int to, int cost) {
        adjacency_list[from].push_back(make_pair(to, cost));
        adjacency_list[to].push_back(make_pair(from, cost));
    }
    int VerticesCount() const {
        return static_cast<int>(adjacency_list.size());

    }
    void GetNextVertices(int vertex, vector<pair<int, int>>& vertices) const {
        vertices.clear();
        for(auto i : adjacency_list[vertex]) {
            vertices.push_back(i);
        }
    }

private:
    vector<vector<pair<int, int>>> adjacency_list;
    //first - dest
    //second - cost
};

class weighted_graph_algorithm {
private:
    const Listgraph* graph;
    
    class Priority_queue {
    private:
        vector<pair<int, int>> distance;
        //first - distance from start_vertex
        //second - number of current vertex
        vector<int> indexes;
        //points to distance with such vertex
        int current_size;

        //restoration of heap's characteristic, saving connection between number and distance
        void sift_down(int i) {
            int min_i = i;
            int left_son = 2 * i + 1;
            int right_son = 2 * i + 2;
            if(left_son < current_size && distance[min_i].first > distance[left_son].first) {
                min_i = left_son;
            }
            if(right_son < current_size && distance[min_i].first > distance[right_son].first) {
                min_i = right_son;
            }
            if(min_i != i) {
                std::swap(distance[min_i], distance[i]);
                std::swap(indexes[distance[min_i].second], indexes[distance[i].second]);
                sift_down(min_i);
            }
        }

        //restoration of heap's characteristic, saving connection between number and distance
        void sift_up(int i) {
            while(i > 0 && distance[i].first < distance[(i - 1) / 2].first ) {
                std::swap(distance[i], distance[(i - 1) / 2]);
                std::swap(indexes[distance[i].second], indexes[distance[(i - 1) / 2].second]);
                i = (i - 1) / 2;
            }
        }

    public:
        Priority_queue(const int amount_of_elements) {
            distance.reserve(amount_of_elements);
            indexes.reserve(amount_of_elements);
            current_size = 0;
        }

        ~Priority_queue() {}

        int size() {
            return  current_size;
        }

        void push(const int dist, const int vertex) {
            distance[current_size] = (make_pair(dist, vertex));
            indexes[vertex] = current_size;
            sift_up(current_size++);
        }

        void change(const int dist, const int vertex) { // change value of distance to current vertex
            distance[indexes[vertex]].first = dist;
            if(distance[indexes[vertex]].first < distance[(indexes[vertex] - 1) / 2].first) {
                sift_up(indexes[vertex]);
            } else {
                sift_down(indexes[vertex]);
            }
        }
        
        int extract_min() { // return number of nearest vertex
            std::swap(distance[0], distance[--current_size]);
            std::swap(indexes[distance[0].second],indexes[distance[current_size].second]);
            sift_down(0);
            return distance[current_size].second;
        }
        
        void print(){
            for(int i = 0; i < current_size; ++i){
                std::cout << distance[i].first<< ' ';
            }
            std::cout << std::endl;
        }
    };
    
public:
    weighted_graph_algorithm(const Listgraph* new_graph) {
        graph = new_graph;
    }
    ~weighted_graph_algorithm() {}

    int dijkstra_(const int from, const int to) {
        vector<bool> visited(graph->VerticesCount(), false);
        vector<int> distance(graph->VerticesCount(), INT16_MAX);
        Priority_queue q(graph->VerticesCount());
        q.push(0, from); //contains pair <num_of_vertex, cost_of_way> ↑
        distance[from] = 0;
        visited[from] = true;

        while (q.size()) {
            int current_vertex = q.extract_min();
            vector<pair<int, int>> next_vertices;
            graph->GetNextVertices(current_vertex, next_vertices);
            for(auto i : next_vertices){
                if(!visited[i.first]) {
                    distance[i.first] = distance[current_vertex] + i.second;
                    q.push(distance[i.first], i.first);
                    visited[i.first] = true;
                } else { //relaxation
                    if (distance[i.first] > distance[current_vertex] + i.second) {
                        distance[i.first] = distance[current_vertex] + i.second;
                        q.change(distance[i.first], i.first);
                    }
                }
            }
        }
        return distance[to];
    }
};

int main() {
    int amount_of_vertices;
    std::cin >> amount_of_vertices;
    int amount_of_edges;
    std::cin >> amount_of_edges;
    Listgraph graph(amount_of_vertices);
    for(int i = 0; i < amount_of_edges; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        graph.AddEdge(from, to, cost);
    }
    weighted_graph_algorithm algorithm(&graph);

    int start, finish;
    std::cin >> start >> finish;

    std::cout << algorithm.dijkstra_(start, finish);
    return 0;
}
