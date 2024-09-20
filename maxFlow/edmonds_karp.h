/// edmonds_karp.h
#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include "graph.h"

int edmondsKarp(Graph& graph, int source, int sink);
int edmondsKarpList(int s, int t, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity);



#endif
