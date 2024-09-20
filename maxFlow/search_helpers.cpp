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
bool bfsList(int s, int t, vector<int>& parent, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; 
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (auto& edge : adj[cur]) {
            int next = edge.first;
            if (parent[next] == -1 && capacity[cur][next] > 0) { 
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return true; 
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

bool dfsList(int s, int t, vector<int>& parent, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    stack<pair<int, int>> stk;
    stk.push({s, INT_MAX});

    while (!stk.empty()) {
        int cur = stk.top().first;
        int flow = stk.top().second;
        stk.pop();

        for (auto& edge : adj[cur]) {
            int next = edge.first;
            if (parent[next] == -1 && capacity[cur][next] > 0) { 
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return true; 
                stk.push({next, new_flow});
            }
        }
    }
    return false;
}
