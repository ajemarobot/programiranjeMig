// search_helpers.h
#ifndef SEARCH_HELPERS_H
#define SEARCH_HELPERS_H

#include "graph.h"
#include <vector>

using namespace std;

bool bfs(Graph& graph, int source, int sink, vector<int>& parent, vector<std::vector<int>>& residualGraph);
bool dfs(Graph& graph, int source, int sink, vector<int>& parent, vector<std::vector<int>>& residualGraph);

#endif
