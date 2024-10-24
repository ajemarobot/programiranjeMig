/// edmonds_karp.cpp
#include "edmonds_karp.h"
#include "search_helpers.h" 

using namespace std;

int edmondsKarp(Graph& graph, int source, int sink) {
    vector<vector<int>> residualGraph = graph.adjMatrix;
    vector<int> parent(graph.V);
    int maxFlow = 0;

    while (bfs(graph, source, sink, parent, residualGraph)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int edmondsKarpList(Graph& graph, int s, int t, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity) {
    int maxFlow = 0;
    vector<int> parent(adj.size(), -1);

    while (bfs(graph, s, t, parent, adj, capacity)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}
