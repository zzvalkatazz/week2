#include<iostream>
#include"adjacency-matirx-graph.h"

void printTupleEdge(const std::tuple<int, int, int>& edge)
{
    std::cout << "(" << std::get<0>(edge)
        << ", " << std::get<1>(edge)
        << ", " << std::get<2>(edge)
        << ")";
}

void printEdges(const std::vector<std::tuple<int, int, int>>& edges)
{
    for (int i = 0; i < edges.size(); i++)
    {
        printTupleEdge(edges[i]);
        std::cout << '\n';
    }
}

int main()
{
    // AdjListGraph g(5, 1);
     AdjMatrixGraph g(5, 1);
   // EdgeListGraph g(5, 1);
    std::cout << "Vertices count: " << g.getVerticesCount() << '\n';

    g.addEdge(0, 2, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(3, 2, 2);
    g.addEdge(4, 2, 3);

    std::cout << "Add vertex: " << g.addVertex() << '\n';
    std::cout << "Add vertex: " << g.addVertex() << '\n';
    std::cout << "Vertices count: " << g.getVerticesCount() << '\n';

    g.removeVertex(3);
    std::cout << "Vertices count: " << g.getVerticesCount() << '\n';

    // g.removeEdge(0, 2);

    std::vector<std::tuple<int, int, int>> edges;
    g.getEdges(edges);
    printEdges(edges);

}