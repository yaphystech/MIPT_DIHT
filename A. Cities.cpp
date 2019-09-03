#include <iostream>
#include <vector>

using std::vector, std::pair, std::make_pair, std::cin, std::cout, std::endl, std::swap;

class ListGraph {
private:
    vector<vector<pair<int, int>>> graph;
    //first - dest
    //second - cost
public:
    ListGraph(const int& amountOfVertices);
    ~ListGraph() {};
    void AddEdge(const int& from, const int& to, const int& cost);
    int VerticesCount() const;
    void GetNextVertices(int& vertex, vector<pair<int, int>>& vertices) const;
};

ListGraph::ListGraph(const int& amountOfVertices) {
    graph.resize(amountOfVertices);
}

void ListGraph::AddEdge(const int& from, const int& to, const int& cost) {
    graph[from].push_back(make_pair(to, cost));
    graph[to].push_back(make_pair(from, cost));
}

int ListGraph::VerticesCount() const {
    return graph.size();

}

void ListGraph::GetNextVertices(int& vertex, vector<pair<int, int>>& vertices) const {
    vertices.clear();
    for(auto i : graph[vertex]) {
        vertices.push_back(i);
    }
}

class ChangeablePriorityQueue {
private:
    vector<pair<int, int>> distance;//first - distance from start_vertex, second - number of current vertex
    vector<int> indexes;//points to distance with such vertex
    int curSize;
    //restoration of heap's characteristic, saving connection between number and distance
    //restoration of heap's characteristic, saving connection between number and distance
public:
    ChangeablePriorityQueue(const int& amountOfElements);
    ~ChangeablePriorityQueue() {}
    void SiftDown(int i);
    void SiftUp(int i);
    int GetSize();
    void Push(const int& dist, const int& vertex);
    void Change(const int& dist, const int& vertex);
    int ExtractMin();//returns number of nearest vertex
    void Print();
};

ChangeablePriorityQueue::ChangeablePriorityQueue(const int& amountOfElements) {
    distance.reserve(amountOfElements);
    indexes.reserve(amountOfElements);
    curSize = 0;
}

void ChangeablePriorityQueue::Push(const int& dist, const int& vertex) {
    distance[curSize] = (make_pair(dist, vertex));
    indexes[vertex] = curSize;
    SiftUp(curSize++);
}

int ChangeablePriorityQueue::GetSize() {
    return  curSize;
}

int ChangeablePriorityQueue::ExtractMin() { // return number of nearest vertex
    swap(distance[0], distance[--curSize]);
    swap(indexes[distance[0].second],indexes[distance[curSize].second]);
    SiftDown(0);
    return distance[curSize].second;
}

void ChangeablePriorityQueue::Change(const int& dist, const int& vertex) { // change value of distance to current vertex
    distance[indexes[vertex]].first = dist;
    if(distance[indexes[vertex]].first < distance[(indexes[vertex] - 1) / 2].first) {
        SiftUp(indexes[vertex]);
    } else {
        SiftDown(indexes[vertex]);
    }
}

void ChangeablePriorityQueue::SiftDown(int i) {
    int minI = i;
    int leftSon = 2 * i + 1;
    int rightSon = 2 * i + 2;
    if(leftSon < curSize && distance[minI].first > distance[leftSon].first) {
        minI = leftSon;
    }
    if(rightSon < curSize && distance[minI].first > distance[rightSon].first) {
        minI = rightSon;
    }
    if(minI != i) {
        swap(distance[minI], distance[i]);
        swap(indexes[distance[minI].second], indexes[distance[i].second]);
        SiftDown(minI);
    }
}

void ChangeablePriorityQueue::SiftUp(int i) {
    while(i > 0 && distance[i].first < distance[(i - 1) / 2].first ) {
        swap(distance[i], distance[(i - 1) / 2]);
        swap(indexes[distance[i].second], indexes[distance[(i - 1) / 2].second]);
        i = (i - 1) / 2;
    }
}

void ChangeablePriorityQueue::Print(){
    for(int i = 0; i < curSize; ++i){
        cout << distance[i].first<< ' ';
    }
    cout << endl;
}

int Dijkstra(const ListGraph& graph, const int& from, const int& to) {
    vector<bool> visited(graph.VerticesCount(), false);
    vector<int> distance(graph.VerticesCount(), INT16_MAX);
    ChangeablePriorityQueue q(graph.VerticesCount());
    q.Push(0, from); //contains pair <numOfVertex, costOfWay> ↑
    distance[from] = 0;
    visited[from] = true;
    while (q.GetSize()) {
        int currentVertex = q.ExtractMin();
        vector<pair<int, int>> nextVertices;
        graph.GetNextVertices(currentVertex, nextVertices);
        for(auto i : nextVertices){
            if(!visited[i.first]) {
                distance[i.first] = distance[currentVertex] + i.second;
                q.Push(distance[i.first], i.first);
                visited[i.first] = true;
            } else { //relaxation
                if (distance[i.first] > distance[currentVertex] + i.second) {
                    distance[i.first] = distance[currentVertex] + i.second;
                    q.Change(distance[i.first], i.first);
                }
            }
        }
    }
    return distance[to];
}

int main() {
    int amountOfVertices;
    cin >> amountOfVertices;
    int amountOfEdges;
    cin >> amountOfEdges;
    ListGraph graph(amountOfVertices);
    for(int i = 0; i < amountOfEdges; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        graph.AddEdge(from, to, cost);
    }
    int start, finish;
    cin >> start >> finish;
    cout << Dijkstra(graph, start, finish);
    return 0;
}
