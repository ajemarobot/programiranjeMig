#include "graph.h"

Graph::Graph(int V) {
    this->V = V;
    adjList.resize(V);
    capacity = vector<vector<int>>(V, vector<int>(V, 0));
}

void Graph::addEdge(int u, int v, int cap) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); 
    capacity[u][v] = cap;
}
