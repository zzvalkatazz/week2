#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
class Graph
{
	int vertices;
	std::vector<std::vector<int>> adjList;
 public:
	Graph(int vertices) : vertices(vertices), adjList(vertices, std::vector<int>()) {}
	Graph(int vertices, std::vector<std::pair<int, int>> edges) : Graph(vertices)
	{
		int edgesCount = edges.size();
		for (int i = 0; i < edgesCount; i++)
		{
			adjList[edges[i].first].push_back(edges[i].second);
			
		}
	}
	void BFS(int start, std::vector<bool>& visited, int& sum, int& vertexCount);

	void DFS(int start);
	void topologicalSort();
 private:
	void DFSUtil(int v, std::vector<bool>& visited);
	void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack);
};
void Graph::DFS(int start)
{
	std::vector<bool> visited(vertices, false);
	DFSUtil(start, visited);
}
void Graph::DFSUtil(int v, std::vector<bool>& visited)
{
	visited[v] = true;
	std::cout << v << " ";

	for (int neighbour : adjList[v])
	{
		if (!visited[neighbour])
		{
			DFSUtil(neighbour, visited);
		}
	}
}
void Graph::topologicalSort()
{
	std::stack<int> Stack;
	std::vector<bool> visited(vertices, false);

	for (int i = 0; i < vertices; i++)
	{
		if (!visited[i])
		{
			topologicalSortUtil(i, visited, Stack);
		}
	}
	std::cout << "Topological sort:\n";
	while (!Stack.empty())
	{
		std::cout << Stack.top() << " ";
		Stack.pop();
	}
	std::cout << std::endl;
}
void Graph::topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack)
{
	visited[v] = true;
	for (int neighbour : adjList[v])
	{
		if (!visited[neighbour])
		{
			topologicalSortUtil(neighbour, visited, Stack);
		}
	}
	Stack.push(v);
}
int main()
{
	int n = 6; // Брой на върховете
	std::vector<std::pair<int, int>> edges = { {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1} };

	Graph g(n, edges);

	std::cout << "DFS от връх 5: ";
	g.DFS(5);

	std::cout << "Топологично сортиране: ";
	g.topologicalSort();

	
	

	return 0;
}