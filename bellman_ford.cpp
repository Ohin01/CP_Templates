#include<bits/stdc++.h>
using namespace std;

const int INF = 1e8 + 9;

vector<vector<int>> edges, graph(2505);
vector<int> dist(2505, INF);

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back(v);
        edges.push_back({u, v, w});

    }
 
    dist[1] = 0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w; 
            }
        }
    }

    int neg = -1;
    
    for (int j = 0; j < edges.size(); j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int w = edges[j][2];
        
        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            dist[v] = dist[u] + w; 
            neg = v;
        }
    }
    
    if (neg == -1) cout << "NO" << endl;
    else cout << "YES" << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}