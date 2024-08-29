#include<iostream>
#include<vector>
#include<queue>

class Graph
{
	int vertices;
	std::vector<std::vector<int>> adjList;
public:
	Graph(int vertices) : vertices(vertices),adjList(vertices,std::vector<int>()){}
	Graph(int vertices, std::vector<std::pair<int, int>> edges) : Graph(vertices)
	{
		int edgesCount = edges.size();
		for (int i = 0; i < edgesCount; i++)
		{
			adjList[edges[i].first].push_back(edges[i].second);
		}
	}

	void getEvenSumOddSum(int start, int& odd, int& even)
	{
		std::queue<std::pair<int, bool>> q;
		std::vector<bool> visited(vertices, false);
		q.push({ start,true });
		visited[start] = true;

		while (!q.empty())
		{
			std::pair<int, bool> current = q.front();
			q.pop();

			if (current.second)
			{
				even += current.first;
			}
			else
			{
				odd += current.first;
			}
			int size = adjList[current.first].size();
			for (int i = 0; i < size; i++)
			{
				int neighbour = adjList[current.first][i];
				if (!visited[neighbour])
				{
					q.push(std::make_pair(neighbour, !current.second));
					visited[neighbour] = true;
				}
			}
		}
	}
};
int main()
{
	int n = 5;
	int m = 7;
	std::vector<std::pair<int, int>> edges = { {0,4},{0,3},{0,1},{1,3},{1,2},{3,2},{4,3} };
	Graph g(n, edges);
	int start = 0;
	int even = 0, odd = 0;
	g.getEvenSumOddSum(start, even, odd);
	std::cout << "Evrn" << even << "\nOdd" << odd;
	std::cout << '\n';
}