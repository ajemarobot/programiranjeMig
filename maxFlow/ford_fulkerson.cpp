/// ford_fulkerson.cpp
#include "ford_fulkerson.h"
#include "search_helpers.h"

using namespace std;

int fordFulkersonDFS(Graph& graph, int source, int sink) {
    vector<vector<int>> residualGraph = graph.adjMatrix;
    vector<int> parent(graph.V);
    int maxFlow = 0;

    while (dfs(graph, source, sink, parent, residualGraph)) {
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
int fordFulkersonList(int s, int t, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity) {
    int maxFlow = 0;
    vector<int> parent(adj.size(), -1);

    while (dfs(s, t, parent, adj, capacity)) {
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
        fill(parent.begin(), parent.end(), -1); 
    }
    return maxFlow;
}

