#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from, to, capacity, flow;
    Edge(int u, int v, int cap) : from(u), to(v), capacity(cap), flow(0) {}
};

class Graph
{
    int V;
    vector<vector<int>> adj;
    vector<Edge> edges;
    vector<int> level;
    vector<int> ptr;

public:
    Graph(int V) : V(V), adj(V), level(V), ptr(V) {}

    void addEdge(int u, int v, int cap)
    {
        edges.push_back(Edge(u, v, cap));
        edges.push_back(Edge(v, u, 0));
        adj[u].push_back(edges.size() - 2);
        adj[v].push_back(edges.size() - 1);
    }

    bool bfs(int source, int sink)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int id : adj[u])
            {
                Edge& e = edges[id];
                if (e.capacity > e.flow && level[e.to] == -1)
                {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int u, int sink, int flow)
    {
        if (flow == 0) return 0;
        if (u == sink) return flow;

        for (int& cid = ptr[u]; cid < adj[u].size(); cid++)
        {
            int id = adj[u][cid];
            Edge& e = edges[id];
            if (level[u] + 1 != level[e.to] || e.capacity == e.flow)
                continue;

            int pushed = dfs(e.to, sink, min(flow, e.capacity - e.flow));
            if (pushed > 0)
            {
                e.flow += pushed;
                edges[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int dinicMaxFlow(int source, int sink)
    {
        int maxFlow = 0;
        while (bfs(source, sink))
        {
            fill(ptr.begin(), ptr.end(), 0);
            while (int flow = dfs(source, sink, INT_MAX))
            {
                maxFlow += flow;
            }
        }
        return maxFlow;
    }

    vector<vector<int>> findDisjointPaths(int source, int sink)
    {
        int flow = dinicMaxFlow(source, sink);

        vector<vector<int>> paths;
        while (true)
        {
            vector<int> parent(V, -1);
            queue<int> q;
            q.push(source);
            while (!q.empty() && parent[sink] == -1)
            {
                int u = q.front();
                q.pop();

                for (int id : adj[u])
                {
                    Edge& e = edges[id];
                    if (e.flow > 0 && parent[e.to] == -1 && e.to != source)
                    {
                        parent[e.to] = id;
                        q.push(e.to);
                    }
                }
            }

            if (parent[sink] == -1) break;

            vector<int> path;
            for (int v = sink; v != source; v = edges[parent[v]].from)
            {
                path.push_back(v);
                edges[parent[v]].flow = 0;
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            paths.push_back(path);
        }
        return paths;
    }
};

int main()
{

    int V = 6;
    Graph g(V);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(2, 5, 1);

    int source = 0;
    int sink = 5;

    auto disjointPaths = g.findDisjointPaths(source, sink);

    for (const auto& path : disjointPaths)
    {
        for (int v : path)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    int timer = 0;
    int b = 0;
    int t = 1;

    for (int i = 0; i <= 100; i += t)
    {
        timer++;
        for (size_t j = 0; j < disjointPaths.size(); )
        {
            const auto& path = disjointPaths[j];

            if (path.size() - 1 <= i)
            {
                if (b == 0)
                {
                    b++;
                    disjointPaths.erase(disjointPaths.begin() + j);

                }
                else
                {
                    t++;
                    disjointPaths.erase(disjointPaths.begin() + j);
                }
            }
            else
            {
                j++;
            }
        }
    }
    cout << timer;


    return 0;
}
