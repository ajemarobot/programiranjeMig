// graph.cpp
#include "graph.h"

using namespace std;

Graph::Graph(int V) : V(V), adjMatrix(V, std::vector<int>(V, 0)), adjList(V) {}

void Graph::addEdgeMatrix(int u, int v, int capacity) {
    adjMatrix[u][v] = capacity;
}

void Graph::addEdgeList(int u, int v, int capacity) {
    adjList[u].emplace_back(v, capacity);
}

void Graph::displayMatrix() const {
    cout << "Adjacency Matrix:"<<endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::displayList() const {
    cout << "Adjacency List:"<<endl;
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (const auto& edge : adjList[i]) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }
}
