/// main.cpp
#include <iostream>
#include "graph.h"
#include "ford_fulkerson.h"
#include "edmonds_karp.h"

int main() {
    int V = 6; 
    Graph graph(V);

    graph.addEdgeMatrix(0, 1, 16);
    graph.addEdgeMatrix(0, 2, 13);
    graph.addEdgeMatrix(1, 2, 10);
    graph.addEdgeMatrix(1, 3, 12);
    graph.addEdgeMatrix(2, 1, 4);
    graph.addEdgeMatrix(2, 4, 14);
    graph.addEdgeMatrix(3, 2, 9);
    graph.addEdgeMatrix(3, 5, 20);
    graph.addEdgeMatrix(4, 3, 7);
    graph.addEdgeMatrix(4, 5, 4);

    cout << "Max Flow (Ford-Fulkerson DFS): " << fordFulkersonDFS(graph, 0, 5) << endl;
	cout << "Max Flow (Ford-Fulkerson BFS): " << fordFulkersonBFS(graph, 0, 5) << endl;

   
