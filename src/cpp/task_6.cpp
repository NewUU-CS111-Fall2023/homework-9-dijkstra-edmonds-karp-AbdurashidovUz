/*
 * Author:
 * Date:
 * Name:
 */

class Problem6 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k, int f) {
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>{});
        for (auto& flight : flights) {
            int from = flight[0];
            int to = flight[1];
            int distance = flight[2];
            int ars = flight[3];
            adj[from].push_back({to, distance, ars});
        }

        priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> pq;
        pq.push({0, src, k, f});

        while (!pq.empty()) {
            auto [cost, current, stops, fuel] = pq.top();
            pq.pop();

            if (current == dst) {
                return cost;
            }

            if (stops < 0 || fuel < 0) {
                continue;
            }

            for (auto& flight : adj[current]) {
                int next = flight.first;
                int distance = flight.second;
                int ars = flight.third;

                if (fuel < distance) {
                    continue; 
                }

                pq.push({cost + distance, next, stops - 1, fuel - distance + ars});
            }
        }

        return -1; // No valid path found
    }
};