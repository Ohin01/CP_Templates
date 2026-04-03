#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MAX = 2e5 + 5;

vvll graph(MAX);
vll intime(MAX, -1);
vll low(MAX, -1);
vb vis(MAX, false);
int timer = 0;
vector<pair<ll, ll>> bridges;
vb points(MAX, false);

void articulation_bridge(ll node, ll par)
{
    timer++;
    vis[node] = true;
    intime[node] = timer;
    low[node] = timer;

    for (auto child: graph[node])
    {
        if (child == par) continue;

        if (vis[child]) low[node] = min(low[node], intime[child]);

        else
        {
            articulation_bridge(child, node);
            low[node] = min(low[node], low[child]);

            if (low[child] > intime[node])
            bridges.push_back({child, node});
        }
    }
}

void articulation_point(ll node, ll par)
{
    timer++;
    vis[node] = true;
    intime[node] = timer;
    low[node] = timer;

    int chcount = 0;

    for (auto child: graph[node])
    {
        if (child == par) continue;

        if (vis[child]) low[node] = min(low[node], intime[child]);

        else
        {
            chcount++;
            articulation_point(child, node);
            low[node] = min(low[node], low[child]);

            if (low[child] >= intime[node] && par != -1)
            points[node] = true;
        }
    }

    if (par == -1 && chcount > 1) 
    points[node] = true;

}

void solve()
{
    
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}