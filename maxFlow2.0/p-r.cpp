#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

const int inf = 1000000000;

vector<vector<int>> flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;

void push(int u, int v, vector<vector<int>>& capacity) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

void relabel(int u, vector<vector<int>>& capacity) {
    int d = inf;
    for (int i = 0; i < capacity.size(); i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

void discharge(int u, vector<vector<int>>& capacity) {
    while (excess[u] > 0) {
        if (seen[u] < capacity.size()) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v, capacity);
            else 
                seen[u]++;
        } else {
            relabel(u, capacity);
            seen[u] = 0;
        }
    }
}

int max_flow(Graph& graph, int s, int t) {
    int n = graph.V;
    vector<vector<int>>& capacity = graph.capacity;
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i, capacity);
    }
    seen.assign(n, 0);

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u, capacity);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}
