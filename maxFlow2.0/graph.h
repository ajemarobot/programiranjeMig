#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

class Graph {
public:
    int V; 
    vector<vector<int>> adjList;  
    vector<vector<int>> capacity; 

    Graph(int V);
    void addEdge(int u, int v, int cap);
};

#endif
