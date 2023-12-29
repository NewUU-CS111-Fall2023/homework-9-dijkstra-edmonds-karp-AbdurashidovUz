#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge {
public:
    int t;      // target node
    int cap;    // capacity
    int flow;   // current flow
    Edge* rev;  // reverse edge

    Edge(int target, int capacity) : t(target), cap(capacity), flow(0), rev(nullptr) {}
};

class Problem2 {
public:
    Problem2(int numNodes) : nodes(numNodes), graph(numNodes) {}

    
    // Time Complexity: O(1)
    void addEdge(int u, int v, int capacity) {
        Edge* uv = new Edge(v, capacity);
        Edge* vu = new Edge(u, 0);  

        uv->rev = vu;
        vu->rev = uv;

        graph[u].push_back(uv);
        graph[v].push_back(vu);
    }

    
    // Time Complexity: O(V * E^2), where V is the number of vertices and E is the number of edges
    int maxFlow(int source, int sink) {
        int flow = 0;

        while (true) {
            vector<Edge*> pred(nodes, nullptr);
            queue<int> q;
            q.push(source);

            while (!q.empty() && pred[sink] == nullptr) {
                int cur = q.front();
                q.pop();

                for (Edge* edge : graph[cur]) {
                    if (!pred[edge->t] && edge->t != source && edge->cap > edge->flow) {
                        pred[edge->t] = edge;
                        q.push(edge->t);
                    }
                }
            }

            if (!pred[sink]) {
                break;
            }

            int minCapacity = INT_MAX;
            for (int node = sink; node != source; node = pred[node]->rev->t) {
                minCapacity = min(minCapacity, pred[node]->cap - pred[node]->flow);
            }

            for (int node = sink; node != source; node = pred[node]->rev->t) {
                pred[node]->flow += minCapacity;
                pred[node]->rev->flow -= minCapacity;
            }

            flow += minCapacity;
        }

        return flow;
    }

private:
    int nodes;
    vector<vector<Edge*>> graph;
};

