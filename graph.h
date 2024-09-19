/// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

class Graph {
public:
    int V; 
    vector<vector<int>> adjMatrix; 
    vector<vector<pair<int, int>>> adjList;

    Graph(int V);
    void addEdgeMatrix(int u, int v, int capacity);
    void addEdgeList(int u, int v, int capacity);
    void displayMatrix() const;
    void displayList() const;
};

#endif
