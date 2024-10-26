#ifndef SEARCH_HELPERS_H
#define SEARCH_HELPERS_H

#include <vector>
#include <queue>
#include <limits>

using namespace std;

bool bfs(const vector<vector<int>>& capacity, const vector<vector<int>>& adjList, int s, int t, vector<int>& parent);

#endif
