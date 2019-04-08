#include <iostream>

#include <vector>

#include <list>



using namespace std;



enum colors{

    white,

    grey,

    black

};



class ListGraph{

private:

    vector<vector<int>> graph;

public:

    ListGraph(int numberOfVertices);

    //~ListGraph();

    int VerticesCount();

    void AddEdge(int from, int to);

    void GetNextVertices(int vertex, vector<int> &vertices);

};



ListGraph::ListGraph(int numberOfVertices) {

    graph.resize(numberOfVertices);

}



void ListGraph::AddEdge(int from, int to) {

    graph[from].push_back(to);

    graph[to].push_back(from);

}



int ListGraph::VerticesCount() {

    return graph.size();

}



void ListGraph::GetNextVertices(int vertex, vector<int> &vertices) {

    vertices = graph[vertex];

}



void DFS(ListGraph& g, int vertex, vector<colors>& visited, vector<int>& timeStart, int parent, bool& flag) {

    vector<int> children;

    g.GetNextVertices(vertex, children);

    visited[vertex] = grey;

    if (parent == -100) {

        timeStart[vertex] = 1;

    } else {

        timeStart[vertex] = timeStart[parent] + 1;

    }

    for(int i = 0; i < children.size(); ++i) {

        if (visited[children[i]] == white) {

            DFS(g, children[i], visited, timeStart, vertex, flag);

        } else {

            if (visited[children[i]] == grey && children[i] != parent) {

                int curLen = timeStart[vertex] - timeStart[children[i]] + 1;

                if(curLen % 2 !=0){

                    flag = false;

                    break;

                }

            }

        }

    }

    visited[vertex] = black;

}



bool MainDFS(ListGraph& g) {

    int amount = g.VerticesCount();

    vector<int> time(amount, 0);

    bool flag = true;

    for (int i = 0; i < amount; ++i) {

        vector<colors> visited(amount, white);

        if(flag){

            DFS(g, i, visited, time, -100, flag);

        }

    }



    return flag;

}

int main() {

    int amountOfVertices = 0, amountOfEdges = 0;

    cin >> amountOfVertices;

    cin >> amountOfEdges;

    ListGraph graph(amountOfVertices);

    for (int i = 0; i < amountOfEdges; ++i) {

        int from, to;

        cin >> from >> to;

        graph.AddEdge(from, to);

    }

    //cout << graph.VerticesCount();

    if(MainDFS(graph)){

        cout << "YES";

    }else{

        cout << "NO";

    }

    return 0;

}
