/// search_helpers.cpp
#include "search_helpers.h"
#include <queue>

using namespace std;

bool bfs(Graph& graph, int source, int sink, vector<int>& parent, vector<vector<int>>& residualGraph) {
    vector<bool> visited(graph.V, false);
    queue<int> queue;
    queue.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                queue.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink)
                    return true;
            }
        }
    }
    return false;
}

bool dfs(Graph& graph, int source, int sink, vector<int>& parent, vector<vector<int>>& residualGraph) {
    vector<bool> visited(graph.V, false);
    vector<int> stack = {source};
    visited[source] = true;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                stack.push_back(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink)
                    return true;
            }
        }
    }
    return false;
}
