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

    cout << "Max Flow (Ford-Fulkerson Matrix): " << fordFulkersonDFS(graph, 0, 5) << endl;
	cout << "Max Flow (Edmonds-Karp Matrix): " << edmondsKarp(graph, 0, 5) << endl;

   int nodes = 6; 
    vector<vector<pair<int, int>>> adj(nodes); 
    vector<vector<int>> capacity(nodes, vector<int>(nodes, 0)); 

    adj[0].push_back({1, 16});
    adj[0].push_back({2, 13});
    adj[1].push_back({2, 10});
    adj[1].push_back({3, 12});
    adj[2].push_back({1, 4});
    adj[2].push_back({4, 14});
    adj[3].push_back({2, 9});
    adj[3].push_back({5, 20});
    adj[4].push_back({3, 7});
    adj[4].push_back({5, 4});

    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[1][3] = 12;
    capacity[2][1] = 4;
    capacity[2][4] = 14;
    capacity[3][2] = 9;
    capacity[3][5] = 20;
    capacity[4][3] = 7;
    capacity[4][5] = 4;

    int source = 0, sink = 5;
    cout << "Maximum Flow (Ford-Fulkerson List): " << fordFulkersonList(source, sink, adj, capacity) << endl;
    cout << "Maximum Flow (Edmonds-Karp List): " << edmondsKarpList(source, sink, adj, capacity) << endl;
    return 0;
	}
