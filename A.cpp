#include <iostream>
#include <vector>

using std::vector, std::swap, std::min, std::pair, std::make_pair, std::cin, std::cout;

class PriorityQueue {
private:
    vector<pair<int, int>> queue; //первое - вершина(второй конец ребра), второе - масса ребра
    vector<int> indexOfEl; //позиция вершины в очереди
    vector<int> isVertexInQueue; //1 - да, 0 - нет
    int curSize;
public:
    PriorityQueue (const int& amountOfElements); //конструктор
    //~PriorityQueue(); //деструктор
    void SiftDown (int i); //просеивание элемента вниз
    void SiftUp (int i); //подъём элемента вверх
    int GetSize (); //получение размера очереди
    void Push (const int& vertex, const int& weight); //добавление элемента в очередь
    void ChangePriority (const int& vertex, const int& weight); //изменение приоритета вершины
    bool IsVertexInPriorQueue (const int& vertex); //проверка вершины на нахождение в очереди в данный момент
    pair<int, int> ExtractMin(); //извлечение минимального по весу ребра из всех смежных для visitedVertices
};

PriorityQueue::PriorityQueue(const int& amountOfElements) {
    queue.reserve(amountOfElements); //резервируем место для всех вершин
    indexOfEl.reserve(amountOfElements); //same
    isVertexInQueue.reserve(amountOfElements);
    curSize = 0; //изначально размер очереди устанавливаем равным нулю
}

bool PriorityQueue::IsVertexInPriorQueue(const int &vertex) {
    return (isVertexInQueue[vertex] == 1);
}

void PriorityQueue::Push(const int& vertex, const int& weight) {
    queue[curSize] = make_pair(vertex, weight);
    indexOfEl[vertex] = curSize;
    isVertexInQueue[vertex] = 1;
    SiftUp(curSize++);
}

int PriorityQueue::GetSize() {
    return curSize;
}

pair<int, int> PriorityQueue::ExtractMin() {
    swap(queue[0], queue[--curSize]); //меняем нулевой элемент с последним
    isVertexInQueue[queue[0].first] = 0;
    swap(indexOfEl[queue[0].first], indexOfEl[queue[curSize].first]); //меняем их позиции
    SiftUp(0); //просеиваем нулевой элемент
    return (queue[curSize]); //возвращаем минимальное в очереди ребро
}

void PriorityQueue::SiftDown(int i) {
    int least = i; //минимальный из вершины и её сыновей
    int leftSon = 2 * i + 1; //левый сын
    int rightSon = 2 * i + 2; //правый сын
    while (2 * least + 1 < curSize && queue[least].second > queue[2 * least + 1].second ||
           2 * least + 2 < curSize && queue[least].second > queue[2 * least + 2].second) //пока можем что-то поменять
    if (leftSon < curSize && queue[least].second > queue[leftSon].second) { //проверка левого сына
        least = leftSon;
    }
    if (rightSon < curSize && queue[least].second > queue[rightSon].second) { //проверка правого сына
        least = rightSon;
    }
    if (least != i) { //если минимальный не i - меняем местами в векторах
        swap(queue[i], queue[least]); //в очереди
        swap(indexOfEl[queue[i].first], queue[least].first); //в векторе индексов
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

class ListGraph {
private:
    vector<vector<pair<int, int>>> graph;
public:
    ListGraph (int amountOfVertices);
    int VerticesCount();
    void AddEdge (int from, int to, int weight);
    void GetNextVertices (int vertex, vector<pair<int, int>>& nextVertices);
    int MinOstWeight(int startVertex, int amountOfVertices);
};

ListGraph::ListGraph(int amountOfVertices) {
    graph.resize(amountOfVertices);
}

int ListGraph::VerticesCount() {
    return graph.size();
}

void ListGraph::AddEdge(int from, int to, int weight) {
    graph[from].push_back({to, weight});
    graph[to].push_back({from, weight});
}

void ListGraph::GetNextVertices(int vertex, vector<pair<int, int>> &nextVertices) {
    nextVertices = graph[vertex];
}

int ListGraph::MinOstWeight(int startVertex, int amountOfVertices) {
    PriorityQueue queue(amountOfVertices);
    vector<int> visitedVertices(1, startVertex); //добавляем стартовую вершину в множество посещённых
    vector<int> isVisited(amountOfVertices, 0);
    isVisited[startVertex] = 1; // явно говорим, что вершина посещена
    vector<pair<int, int>> nextVertices; //вектор пар <int, int>, первое - вершина, второе - масса ребра
    int minweight = 0; //вес минимального остовного дерева
    int vertex = startVertex;
    pair<int, int> minEdge = {startVertex, 0};
    while (visitedVertices.size() != graph.size()) { //пока не посетим все вершины
        GetNextVertices(vertex, nextVertices); //находим смежные рёбра для вершины vertex
        for (auto i : nextVertices) { //проходимся по смежным рёбрам
            if (isVisited[i.first] == 0) {
                if (queue.IsVertexInPriorQueue(i.first)) { //если вершина в данный момент в очереди
                    queue.ChangePriority(i.first, i.second); //пытаемся поменять её приоритет
                } else {
                    queue.Push(i.first, i.second); //иначе добавляем элемент в очередь
                }
            }
        }
        minEdge = queue.ExtractMin(); //извлекаем минимальное ребро
        minweight += minEdge.second; //увеличиваем массу минимального остовного дерева
        visitedVertices.push_back(minEdge.first); //помечаем вершину посещённой
        isVisited[minEdge.first] = 1; //same
        vertex = minEdge.first; //переходим к следующей вершине
    }
    return minweight;
}

int main() {
    int amountOfVertices, amountOfEdges;
    cin >> amountOfVertices >> amountOfEdges;
    ListGraph graph(amountOfVertices);
    for (int i = 0; i < amountOfEdges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    cout << graph.MinOstWeight(0, amountOfVertices);
    return 0;
}
