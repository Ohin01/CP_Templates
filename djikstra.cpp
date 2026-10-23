#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

void dijkstra(int V, vector<vector<pair<int, int>>> &adj, int src) {
    vector<int> dist(V, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) 
    {
        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currDist > dist[u]) continue;

        for (auto edge : adj[u]) 
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < V; i++) {
        cout << i << " " << dist[i] << "\n";
    }
}