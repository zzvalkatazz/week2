#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> convertToAdjacencyList(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adjList(n);
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // Графът е неориентиран, затова добавяме и в двете посоки
    }
    return adjList;
}
vector<int> citiesWithinPDistance(const vector<vector<int>>& adjList, int startCity, int p) {
    vector<int> result;
    vector<int> distance(adjList.size(), -1);
    queue<int> q;

    q.push(startCity);
    distance[startCity] = 0;

    while (!q.empty())
    {
        int city = q.front();
        q.pop();

        if (distance[city] <= p)
        {
            result.push_back(city);
        }
        for (int neighbour : adjList[city])
        {
            if (distance[neighbour] == -1)
            {
                distance[neighbour] = distance[city] + 1;
                if (distance[neighbour] <= p)
                {
                    q.push(neighbour);
                }
            }
        }
    }
    return result;
}
bool compareByLandmarks(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;  // Сортираме в низходящ ред по броя на забележителностите
}

vector<int> topKCitiesWithLandsmarks(const vector<int>& cities, const vector<int>& landmarks,int k)
{
    vector<pair<int, int>> cityLandmarks;
    for (int city : cities)
    {
        cityLandmarks.push_back({ city,landmarks[city] });
    }
    sort(cityLandmarks.begin(), cityLandmarks.end(), compareByLandmarks);
    vector<int> topKCitites;
    for (int i = 0; i < k && i < cityLandmarks.size(); i++)
    {
        topKCitites.push_back(cityLandmarks[i].first);
    }
    return topKCitites;
}\
int main()
{
    int n = 6;
    vector<pair<int, int>> edges = { {0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 5} };
    vector<int> landmarks = { 3, 1, 4, 2, 5, 0 };
    int startCity = 0;  // Начален град
    int p = 2;  // Най-много p часа път
    int k = 3;
    vector<vector<int>> adjList = convertToAdjacencyList(n, edges);
    vector<int> reachableCities = citiesWithinPDistance(adjList, startCity, p);

    vector<int> topK = topKCitiesWithLandsmarks(reachableCities, landmarks, k);
    for (int reach : reachableCities)
    {
        cout << reach << " ";
    }
    cout << endl;
    for (int city : topK) {
        cout << "Град: " << city << ", Забележителности: " << landmarks[city] << endl;
    }
}


