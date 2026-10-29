#include<bits/stdc++.h>
using namespace std;

int primsMST(int V, vector<vector<int>> &edges) 
{
    // code here
    vector<vector<pair<int, int>>> g(V + 1);
    int n = V;
    
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    vector<bool> vis(n + 1);
    
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>> pq;
        
    pq.push({0, 0, 0});
    //vis[0] = true;
    int ans = 0;
    
    while (!pq.empty())
    {
        tuple<int, int, int> t = pq.top();
        pq.pop();
        
        int u = get<1>(t);
        int v = get<2>(t);
        int w = get<0>(t);
        
        if (vis[v] == true) continue;
        
        vis[v] = true;
        ans += w;
        
        for (auto &p: g[v])
        {
            int ch = p.first;
            int wt = p.second;
            
            if (vis[ch] == true) continue;
            
            pq.push({wt, v, ch});
        }
    }
    return ans;
}