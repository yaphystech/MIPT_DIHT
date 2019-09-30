#include <iostream>
#include <vector>
#include <stack>

using std::vector, std::stack, std::cin, std:: cout, std::numeric_limits;

const int Infinity = numeric_limits<int>::max();

class ListGraph {
private:
    vector<vector<int>> inEdges;
    vector<vector<int>> outEdges;
public:
    ListGraph (const int& amountOfVertices);
    ~ListGraph() {};
    vector<int> GetNextVertices(const int& vertex) const;
    vector<int> GetPrevVertices(const int& vertex) const;
    int VerticesCount () const;
    void AddEdge (int& from, int& to);
};

ListGraph::ListGraph(const int &amountOfVertices) {
    inEdges.resize(amountOfVertices);
    outEdges.resize(amountOfVertices);
}

void ListGraph::AddEdge(int &from, int &to) {
    outEdges[from].push_back(to);
    inEdges[to].push_back(from);
}

vector<int> ListGraph::GetNextVertices(const int& vertex) const {
    return outEdges[vertex];
}

vector<int> ListGraph::GetPrevVertices(const int& vertex) const {
    return inEdges[vertex];
}

int ListGraph::VerticesCount() const {
    return outEdges.size();
}

void TestVertexOnRoot(const int& testVertex, ListGraph& graph, vector<int>& components, int& time,
                      vector<bool>& visited, vector<int>& lowLink, stack<int>& stack, int& amountOfComponents) {
    stack.push(testVertex); //добавляем вершину во вспомогательный стэк
    lowLink[testVertex] = time; //хранит чиселку, одинаковую для всей ССК
    visited[testVertex] = true; //отмечаем вершину как посещённую
    bool isComponentRoot = true; // булевская константа, отвечающая за поиск уникальной ССК
    time += 1;
    for (int v : graph.GetNextVertices(testVertex)) {
        if (!visited[v]) { //если вершина не посещена, тестим её
            TestVertexOnRoot(v, graph, components, time, visited, lowLink, stack, amountOfComponents);
        }
        if (lowLink[testVertex] > lowLink[v]) { //пришли из большего в меньший
            lowLink[testVertex] = lowLink[v]; //присваеваем большему меньший
            isComponentRoot = false; //в этой вершине новой компоненты не добавляется (этот блок нужен для того, чтобы каждую компоненту считать
        } //ровно один раз
    }
    if (isComponentRoot) { //если нашли ССК
        while (!stack.empty()) {
            int vertex = stack.top(); //запоминаем верхнюю вершину стека
            stack.pop(); //затем убираем её из стека
            components[vertex] = amountOfComponents; //приписываем этой вершине ССК
            lowLink[vertex] = Infinity;
            if (vertex == testVertex) { //если дошли до нашей вершины - выходим из цикла
                break;
            }
        }
        amountOfComponents += 1; //увеличиваем число ССК на единицу
    }
}

int AmountOfMissingEdges(ListGraph &graph, vector<int> &components, const int &amountOfComponents) {
    ListGraph connectedComponentsGraph(amountOfComponents); //граф компонент
    for (int i = 0; i < graph.VerticesCount(); ++i) { //проходимся по всем вершинам исходного графа
        for (int j : graph.GetNextVertices(i)) { //для каждой вершины проходимся по её детям
            if (components[i] != components[j]) { //если они лежат в разных ССК
                connectedComponentsGraph.AddEdge(components[i], components[j]); //добавляем ребро в созданный граф
            }
        }
    }
    int begs = 0, ends = 0; //begs и ends - число соответствующих ориентированных рёбер между компонентами
    for (int j = 0; j < connectedComponentsGraph.VerticesCount(); ++j) {
        if (connectedComponentsGraph.GetNextVertices(j).size() == 0) {
            ends += 1;
        }
        if (connectedComponentsGraph.GetPrevVertices(j).size() == 0) {
            begs += 1;
        }
    }
    int res = begs > ends ? begs : ends; //выбираем максимум из рёбер, "входящих" в ССК, которые нужно добавить, и необходимых для сильной связности "исходящих" рёбер
    if (amountOfComponents == 1) { //если ССК одна, то никаких рёбер добавлять не нужно
        res = 0; //то есть res == 0
    }
    return res;
}

vector<int> Tarjan(ListGraph& graph, int& amountOfComponents) { //не const ListGraph& чисто из-за того, что вызов функции происходит после добавления элементов
    vector<int> components(graph.VerticesCount()); //вектор с id компонент
    int time = 0;
    stack<int> stack; //вспомогательный стэк
    vector<bool> visited(graph.VerticesCount()); //вектор, отображающий, посещена ли вершина или нет
    vector<int> lowLink(graph.VerticesCount()); //вектор, в котором хранится индекс вершины
    for (int i = 0; i < graph.VerticesCount(); ++i) { //проходимся по всем вершинам
        if (!visited[i]) { //если вершина не посещена, проверяем её на корень ССК
            TestVertexOnRoot(i, graph, components, time, visited, lowLink, stack, amountOfComponents);
        }
    }
    return components; //возвращаем вектор компонент
}

int main() {
    int amountOfVertices, amountOfEdges;
    cin >> amountOfVertices >> amountOfEdges;
    ListGraph graph(amountOfVertices);
    for (int i = 0; i < amountOfEdges; i++) {
        int from, to;
        cin >> from >> to;
        graph.AddEdge(--from, --to);
    }
    int amountOfComponents = 0;
    vector<int> components = Tarjan(graph, amountOfComponents);
    cout << AmountOfMissingEdges(graph, components, amountOfComponents);
    return 0;
}
