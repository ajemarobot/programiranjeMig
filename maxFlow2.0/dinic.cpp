#include "dinic.h"
#include "search_helpers.h"

bool bfsLevelGraph(const vector<vector<int>>& capacity, const vector<vector<int>>& adjList, vector<int>& level, int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adjList[u]) {
            if (level[v] < 0 && capacity[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[t] >= 0;
}

int dfs(vector<vector<int>>& capacity, const vector<vector<int>>& adjList, vector<int>& level, vector<int>& start, int u, int t, int flow) {
    if (u == t) return flow;

    for (int& i = start[u]; i < adjList[u].size(); ++i) {
        int v = adjList[u][i];

        if (level[v] == level[u] + 1 && capacity[u][v] > 0) {
            int currFlow = min(flow, capacity[u][v]);
            int tempFlow = dfs(capacity, adjList, level, start, v, t, currFlow);

            if (tempFlow > 0) {
                capacity[u][v] -= tempFlow;
                capacity[v][u] += tempFlow;
                return tempFlow;
            }
        }
    }

    return 0;
}

int dinic(Graph& g, int s, int t) {
    vector<vector<int>> capacity = g.capacity;
    vector<int> level(g.V), start(g.V);
    int maxFlow = 0;

    while (bfsLevelGraph(capacity, g.adjList, level, s, t)) {
        fill(start.begin(), start.end(), 0);

        while (int flow = dfs(capacity, g.adjList, level, start, s, t, numeric_limits<int>::max())) {
            maxFlow += flow;
        }
    }

    return maxFlow;
}
