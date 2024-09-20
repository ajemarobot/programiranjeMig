/// ford_fulkerson.h
#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "graph.h"

int fordFulkersonDFS(Graph& graph, int source, int sink);
int fordFulkersonList(int s, int t, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity);

#endif
