#include "edmonds_karp.h"

int edmondsKarp(Graph& g, int s, int t) {
    vector<vector<int>> capacity = g.capacity;
    vector<int> parent(g.V);
    int maxFlow = 0;

    while (bfs(capacity, g.adjList, s, t, parent)) {
        int pathFlow = numeric_limits<int>::max();

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
