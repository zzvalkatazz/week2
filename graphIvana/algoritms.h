#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "graph.h"
#include<queue>
#include<stack>
#include<climits>

void BFS(const Graph& g, int start, std::vector<int>& order);
void DFS(const Graph& g, int start, std::vector<int>& order);
void DFS_rec(const Graph& g, int start, std::vector<bool>& visited);

#endif