class Problem5 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n,vector<pair<int,int>>{});
        for(auto x:flights){
            adj[x[0]].push_back({x[1],x[2]});
        }

        queue<pair<int,pair<int,int>>> q;
        vector<int> dist(n,1e9);
        dist[src]=0;
        q.push({0,{src,0}});

        while(!q.empty()){
            auto front=q.front();
            q.pop();
            int stops=front.first;
            int cost=front.second.second;
            int node=front.second.first;

            if(stops>k){continue;}

            for(auto it:adj[node]){
                if(cost+it.second < dist[it.first] && stops<=k){
                    dist[it.first]=cost+it.second;
                    q.push({stops+1,{it.first,dist[it.first]}});
                }
            }
        }

        if(dist[dst]!=1e9){return dist[dst];}
        return -1;
    }
};