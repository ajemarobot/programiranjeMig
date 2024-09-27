#include "MIN_CUT_AND_DISJOINT_PATHS.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

vector<int> findMinCut(Graph& g, int source) {
    vector<bool> visited(g.V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g.adj[u]) {
            if (!visited[v] && g.capacity[u][v] > 0) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    vector<int> minCutVertices;
    for (int i = 0; i < g.V; i++) {
        if (visited[i]) {
            minCutVertices.push_back(i);
        }
    }
    return minCutVertices;
}

vector<pair<int, vector<int>>> maxDisjointPaths(Graph& g, int source, int sink) {
    vector<pair<int, vector<int>>> disjointPaths;
    int maxFlow = g.edmondsKarp(source, sink);

    while (true) {
        vector<int> parent(g.V, -1);
        if (!g.bfs(source, sink, parent)) {
            break;
        }

        vector<int> path;
        int pathFlow = numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path.push_back(u);
            pathFlow = min(pathFlow, g.capacity[u][v]);
        }
        path.push_back(sink);
        reverse(path.begin(), path.end());
        disjointPaths.emplace_back(path.size()-1, path);

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            g.capacity[u][v] -= pathFlow;
            g.capacity[v][u] += pathFlow;
        }
    }
    return disjointPaths;
}

void antz(Graph& g, int source, int sink) {
    auto disjointPaths = maxDisjointPaths(g, source, sink);
    int time = 0;
	bool b=0;

    for (int t = 1, i = 0; i <= 100; i += t) {
        time++;
        for (const auto& p : disjointPaths) {
            if (i > p.first) {
                if(b==1)t++;
				else b=1;
                break;
            }
        }
    }

    return time;
}
