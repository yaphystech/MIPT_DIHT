#include <iostream>
#include <vector>

using std::vector, std::swap, std::min, std::pair, std::make_pair, std::cin, std::cout, std::endl;

class PriorityQueue {
private:
    vector<pair<int, int>> queue; //первое - вершина(второй конец ребра), второе - масса ребра
    vector<int> indexOfEl; //позиция вершины в очереди
    vector<bool> isVertexInQueue; //true - да, false - нет
    int curSize;
public:
    PriorityQueue (const int& amountOfElements); //конструктор
    ~PriorityQueue() {}; //деструктор
    void SiftDown (int i); //просеивание элемента вниз
    void SiftUp (int i); //подъём элемента вверх
    int GetSize (); //получение размера очереди
    void Push (const int& vertex, const int& weight); //добавление элемента в очередь
    void ChangePriority (const int& vertex, const int& weight); //изменение приоритета вершины
    bool IsVertexInPriorQueue (const int& vertex); //проверка вершины на нахождение в очереди в данный момент
    pair<int, int> ExtractMin(); //извлечение минимального по весу ребра из всех смежных для visitedVertices
};

PriorityQueue::PriorityQueue(const int& amountOfElements) {
    queue.resize(amountOfElements); //резервируем место для всех вершин
    indexOfEl.resize(amountOfElements); //same
    isVertexInQueue.resize(amountOfElements, false);
    curSize = 0; //изначально размер очереди устанавливаем равным нулю
}

bool PriorityQueue::IsVertexInPriorQueue(const int& vertex) {
    return isVertexInQueue[vertex];
}

void PriorityQueue::Push(const int& vertex, const int& weight) {
    queue[curSize] = {vertex, weight};
    indexOfEl[vertex] = curSize;
    isVertexInQueue[vertex] = true;
    SiftUp(curSize++);
}

int PriorityQueue::GetSize() {
    return curSize;
}

pair<int, int> PriorityQueue::ExtractMin() {
    isVertexInQueue[queue[0].first] = 0;
    swap(queue[0], queue[--curSize]); //меняем нулевой элемент с последним
    swap(indexOfEl[queue[0].first], indexOfEl[queue[curSize].first]); //меняем их позиции
    SiftDown(0); //просеиваем нулевой элемент
    return (queue[curSize]); //возвращаем минимальное в очереди ребро
}

void PriorityQueue::SiftDown(int i) {
    int least = i; //минимальный из вершины и её сыновей
    int leftSon = 2 * i + 1; //левый сын
    int rightSon = 2 * i + 2; //правый сын
    while (2 * least + 1 < curSize && queue[least].second > queue[2 * least + 1].second ||
           2 * least + 2 < curSize && queue[least].second > queue[2 * least + 2].second) { //пока можем что-то поменять
        if (leftSon < curSize && queue[least].second > queue[leftSon].second) { //проверка левого сына
            least = leftSon;
        }
        if (rightSon < curSize && queue[least].second > queue[rightSon].second) { //проверка правого сына
            least = rightSon;
        }
        if (least != i) { //если минимальный не i - меняем местами в векторах
            swap(queue[i], queue[least]); //в очереди
            swap(indexOfEl[queue[i].first], indexOfEl[queue[least].first]); //в векторе индексов
            i = least;
            leftSon = 2 * i + 1; //левый сын
            rightSon = 2 * i + 2;
        }
    }
}

void PriorityQueue::SiftUp(int i) {
    while (i > 0 && queue[i].second < queue[(i - 1) / 2].second) { // пока родитель меньше и пока i > 0
        swap(queue[i], queue[(i - 1) / 2]); //меняем вершины
        swap(indexOfEl[queue[i].first], indexOfEl[queue[(i - 1) / 2].first]); //меняем позиции вершин
        i = (i - 1) / 2; //поднимаемся в родительскую вершину
    }
}

void PriorityQueue::ChangePriority(const int& vertex, const int& weight) {
    if (queue[indexOfEl[vertex]].second > weight) {
        queue[indexOfEl[vertex]].second = weight;
        if (queue[indexOfEl[vertex]].second < queue[(indexOfEl[vertex] - 1) / 2].second) { //если меньше вершины -
            SiftUp(indexOfEl[vertex]); // поднимаем вверх
        } else {
            SiftDown(indexOfEl[vertex]); //иначе просеиваем вниз
        }
    }
}

class MatrixGraph {
private:
    vector<vector<int>> graph;
public:
    MatrixGraph (int amountOfVertices);
    int VerticesCount();
    void AddEdge (int from, int to, int weight);
    void GetNextVertices (int vertex, vector<pair<int, int>>& nextVertices);
    int MinOstWeight(int startVertex, int amountOfVertices);//считает вес минимального остовного
    void AddAdjactencyEdgesToQueue(vector<pair<int, int>>& adjacentEdges, vector<bool>& isVisited, PriorityQueue& queue); //пробная функция, добавляет все рёбра из nextVertices в Priority Queue
    void Print(int vertex);
};

MatrixGraph::MatrixGraph (int amountOfVertices) {
    graph.resize(amountOfVertices);
    for (int i = 0; i < amountOfVertices; ++i) {
        graph[i].resize(amountOfVertices);
        for (int j = 0; j < graph[i].size(); ++j) {
            graph[i][j] = 0;
        }
    }
};

void MatrixGraph::Print(int vertex) {
    for (int i = 0; i < graph[vertex].size(); ++i) {
        cout << i << ' '<< graph[vertex][i] << endl;
    }
}

void MatrixGraph::AddAdjactencyEdgesToQueue(vector<pair<int, int>>& adjacentEdges, vector<bool>& isVisited, PriorityQueue& queue) { //обрабатывает рёбра из adjacentEdges
    for (auto i : adjacentEdges) { //проходимся по смежным рёбрам
        if (!isVisited[i.first]) { //если второй конец не посещён
            if (queue.IsVertexInPriorQueue(i.first)) { //если вершина в данный момент в очереди
                queue.ChangePriority(i.first, i.second); //пытаемся поменять её приоритет
            } else {
                queue.Push(i.first, i.second); //иначе добавляем элемент в очередь
            }
        }
    }
}

int MatrixGraph::VerticesCount() {
    return graph.size();
}

void MatrixGraph::AddEdge(int from, int to, int weight) {
    if (graph[from][to] == 0) {
        graph[from][to] = weight;
        graph[to][from] = weight;
    } else {
        if (graph[from][to] > weight) {
            graph[from][to] = weight;
            graph[to][from] = weight;
        }
    }
}

void MatrixGraph::GetNextVertices(int vertex, vector<pair<int, int>>& nextVertices) {
    for (int i = 0; i < graph[vertex].size(); ++i) {
        if (graph[vertex][i] != 0) {
            nextVertices.push_back({i, graph[vertex][i]});
        }
    }
}

int MatrixGraph::MinOstWeight(int startVertex, int amountOfVertices) {
    PriorityQueue queue(amountOfVertices);
    int amountOfVisitedVertices = 1;
    vector<bool> isVisited(amountOfVertices, 0);
    isVisited[startVertex] = 1; // явно говорим, что вершина посещена
    vector<pair<int, int>> adjacentEdges; //вектор пар <int, int>, первое - вершина, второе - масса ребра
    int minWeight = 0; //вес минимального остовного дерева
    int vertex = startVertex;
    pair<int, int> minEdge = {startVertex, 0};
    while (amountOfVisitedVertices != graph.size()) { //пока не посетим все вершины
        GetNextVertices(vertex, adjacentEdges); //находим смежные рёбра для вершины vertex
        AddAdjactencyEdgesToQueue(adjacentEdges, isVisited, queue);//обрабатывает рёбра из вектора adjacentEdges
        minEdge = queue.ExtractMin(); //извлекаем минимальное ребро
        minWeight += minEdge.second; //увеличиваем массу минимального остовного дерева
        ++amountOfVisitedVertices; //помечаем вершину посещённой
        isVisited[minEdge.first] = true; //same
        vertex = minEdge.first; //переходим к следующей вершине
        adjacentEdges.clear();
    }
    return minWeight;
}

int main() {
    int amountOfVertices, amountOfEdges;
    cin >> amountOfVertices >> amountOfEdges;
    MatrixGraph graph(amountOfVertices);
    for (int i = 0; i < amountOfEdges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        if (from != to) {
            graph.AddEdge(from - 1, to - 1, weight);
        }
    }
    cout << graph.MinOstWeight(0, amountOfVertices);
    //graph.Print(5);
    return 0;
}
