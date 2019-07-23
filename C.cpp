#include <iostream>
#include <vector>
#include <queue>

using std::vector, std::queue, std::cin, std::cout;

class ListGraph {
private:
    int size;
    std::vector<std::vector<int>> graph;
public:
	ListGraph(int _size) : graph(_size), size(_size) {};
	void AddEdge(const int& from, const int& to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, vector<int>& vertices) const;
};

void ListGraph::AddEdge(const int& from, const int& to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
};

int ListGraph::VerticesCount() const {
    return size;
};

void ListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices = graph[vertex];
};

struct state {
	state() = default;
	state(int d, int p): depth(d), paths(p) {}
	int depth = 0;
	int paths = 0;
};

int NumbersOfWays(const ListGraph myGraph, int& start, int& end) {
	queue<int> bfs_queue; //стандартная очередь для BFS
	bfs_queue.push(start);
	vector<state> states(myGraph.VerticesCount(), state()); //хранит минимальную глубину и количество путей в i
	states[start].depth = 1;
	states[start].paths = 1;
	while (!bfs_queue.empty()) {
		int cur = bfs_queue.front();
		bfs_queue.pop();
		vector<int> vertices;
        myGraph.GetNextVertices(cur, vertices);
		for (int i : vertices) {
			if (states[i].depth == 0) {
			    states[i] = state(states[cur].depth + 1, states[cur].paths); bfs_queue.push(i);
			}
			else if (states[i].depth == states[cur].depth + 1) {
			    states[i].paths += states[cur].paths;
			}
		}
	}
	return states[end].paths;
}

int main() {
	int amountOfVertices, amountOfEdges;
	cin >> amountOfVertices >> amountOfEdges;
	ListGraph graph(amountOfVertices);
	for (int i = 0; i < amountOfEdges; i++) {
		int from, to;
		cin >> from >> to;
		graph.AddEdge(from, to);
	}
	int v, w;
	cin >> v >> w;
	cout << NumbersOfWays(graph, v, w);
    return 0;
}
