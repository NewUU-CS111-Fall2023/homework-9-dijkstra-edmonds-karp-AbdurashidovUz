#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Problem1 {
public:

    Problem1(int numVertices) : vertices(numVertices), adjList(numVertices) {}

    
    // Time Complexity: O(1) - Adding an edge to the adjacency list

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    
    // Time Complexity: O((V + E) * log(V)), where V is the number of vertices and E is the number of edges

    vector<int> shortestDistances(int start) {
        vector<int> dist(vertices, INF);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (currentDist > dist[u]) continue;

            for (const auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }

private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
};
