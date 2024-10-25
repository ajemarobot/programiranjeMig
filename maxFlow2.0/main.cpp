#include "graph.h"
#include "edmonds_karp.h"
#include "ford_fulkerson.h"
#include "dinic.h"

int main() {
    int V = 6;
    Graph g(V);

    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    int s = 0, t = 5;

    cout << "Edmonds-Karp Max Flow: " << edmondsKarp(g, s, t) << endl;
    cout << "Ford-Fulkerson Max Flow: " << fordFulkerson(g, s, t) << endl;
    cout << "Dinic Max Flow: " << dinic(g, s, t) << endl;

  
    return 0;
}
