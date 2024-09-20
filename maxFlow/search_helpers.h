// search_helpers.h
#ifndef SEARCH_HELPERS_H
#define SEARCH_HELPERS_H

#include "graph.h"
#include <vector>
#include <utility>

using namespace std;

bool bfs(Graph& graph, int source, int sink, vector<int>& parent, vector<vector<int>>& residualGraph);
bool dfs(Graph& graph, int source, int sink, vector<int>& parent, vector<vector<int>>& residualGraph);

bool bfsList(int s, int t, vector<int>& parent, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity);
bool dfsList(int s, int t, vector<int>& parent, vector<vector<pair<int, int>>>& adj, vector<vector<int>>& capacity);

#endif
