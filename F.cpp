#include <iostream>
#include <vector>
#include <stack>

const int Infinity = (unsigned int)~0 >> 1;

using std::vector, std::stack, std::cin, std:: cout;

class ListGraph{
private:
	int size;
	vector<std::vector<int>> outEdges;
	vector<std::vector<int>> inEdges;
public:
	ListGraph(int _size) : inEdges(_size), outEdges(_size), size(_size) {};
	~ListGraph(){};
	void AddEdge(const int& from, const int& to);
	int VerticesCount() const;
	vector<int> GetNextVertices(const int& vertex) const;
	vector<int> GetPrevVertices(const int& vertex) const;
};

void ListGraph::AddEdge(const int& from, const int& to) {
	outEdges[from].push_back(to); inEdges[to].push_back(from);
}

int ListGraph::VerticesCount() const {
	return size;
}

vector<int> ListGraph::GetNextVertices(const int& vertex) const {
	return outEdges[vertex];
}

vector<int> ListGraph::GetPrevVertices(const int& vertex) const {
	return inEdges[vertex];
}

int getResult(ListGraph& graph, vector<int>& components, const int& amountOfComponents) {
	ListGraph conGraph(amountOfComponents);
	for (int i = 0; i < graph.VerticesCount(); ++i)
		for (int j : graph.GetNextVertices(i))
			if (components[i] != components[j]) {
				conGraph.AddEdge(components[i], components[j]);
			}
	int begs = 0, ends = 0;
	for (int j = 0; j < conGraph.VerticesCount(); ++j) {
		if (conGraph.GetNextVertices(j).size() == 0) {
			ends += 1;
		}
		if (conGraph.GetPrevVertices(j).size() == 0) {
			begs += 1;
		}
	}
	int res = begs > ends ? begs : ends;
	if (amountOfComponents == 1) {
		res = 0;
	}
	return res;
}

void TestVertexOnRoot(const int& testVertex, ListGraph& graph, vector<int>& components, int& time,
	vector<bool>& visited, vector<int>& lowLink, stack<int>& stack, int& amountOfComponents) {
	stack.push(testVertex);
	lowLink[testVertex] = time;
	visited[testVertex] = true;
	bool isComponentRoot = true;
	time += 1;
	for (int v : graph.GetNextVertices(testVertex)) {
		if (!visited[v]) {
			TestVertexOnRoot(v, graph, components, time, visited, lowLink, stack, amountOfComponents);
		}
		if (lowLink[testVertex] > lowLink[v]) {
			lowLink[testVertex] = lowLink[v];
			isComponentRoot = false;
		}
	}
	if (isComponentRoot) {
		while (true) {
			int x = stack.top();
			stack.pop();
			components[x] = amountOfComponents;
			lowLink[x] = Infinity;
			if (x == testVertex) {
				break;
			}
		}
		amountOfComponents += 1;
	}
}

vector<int> Tarjan(ListGraph& graph, int& amountOfComponents) {
	vector<int> components(graph.VerticesCount());
	int time = 0;
	stack<int> stack;
	vector<bool> visited(graph.VerticesCount());
	vector<int> lowLink(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); i++)
		if (!visited[i]) {
			TestVertexOnRoot(i, graph, components, time, visited, lowLink, stack, amountOfComponents);
		}
	return components;
}

/*Граф разделяется на компоненты связности, и смотрим как их нужно досоединить*/
int main() {
	int amountOfVertices, amountOfEdges;
	cin >> amountOfVertices >> amountOfEdges;
	ListGraph graph(amountOfVertices);
	for (int i = 0; i < amountOfEdges; i++) {
		int from, to;
		cin >> from >> to;
		graph.AddEdge(from - 1, to - 1);
	}
	int amountOfComponents = 0;
	vector<int> components = Tarjan(graph, amountOfComponents);
	cout << getResult(graph, components, amountOfComponents);
    return 0;
}
