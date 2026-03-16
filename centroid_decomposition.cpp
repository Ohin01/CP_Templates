#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX = 2e5 + 5;
const int LOGN = 20;
const int INF = 1e9 + 7;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

vector<int> g[MAX]; 
int par[MAX][LOGN];
int depth[MAX];

int sz[MAX];
int done[MAX];
int cenpar[MAX];
int tot;

void dfs_lca(int node, int p) 
{
    par[node][0] = p;
 
    for (auto child : g[node]) 
    {
        if (child == p) continue;
        depth[child] = depth[node] + 1;
        dfs_lca(child, node);
    }
}

void fillAncestor(int n) 
{
    for (int i = 1; i < LOGN; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (par[j][i - 1] != 0)
                par[j][i] = par[par[j][i - 1]][i - 1];
            else
                par[j][i] = 0;
        }
    }
}

int kthAncestor(int node, int k)
{
    int ans = node;

    FOR(i, 0, LOGN)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i]; 
            if (ans == 0) return 0;
        }
    }

    return ans;
}

int LCA(int n1, int n2)
{
    if (depth[n1] > depth[n2]) swap(n1, n2);

    int diff = depth[n2] - depth[n1];
    n2 = kthAncestor(n2, diff);

    if (n1 == n2) return n1;

    FORR(i, LOGN - 1, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    return par[n1][0];
}

int get_dist(int u, int v) 
{
    if (u <= 0 || v <= 0) return INF; 
    return depth[u] + depth[v] - 2 * depth[LCA(u, v)];
}

void calc_sz(int u, int p) //always calc the new sizes
{
    tot++;
    sz[u] = 1;
    for (auto v : g[u]) 
    {
        if (v == p || done[v]) continue; //done means its a centroid
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

int find_cen(int u, int p) //typical centroid find
{
    for (auto v : g[u]) 
    {
        if (v == p || done[v]) continue;
        if (sz[v] > tot / 2) return find_cen(v, u);
    }
    return u;
}

void decompose(int u, int pre) 
{
    tot = 0;
    calc_sz(u, -1);
    int cen = find_cen(u, -1);
    
    cenpar[cen] = pre; // pre is the parent in the Centroid Tree
    done[cen] = 1;

    //Do operation here right after breaking into components
    
    for (auto v : g[cen]) 
    {
        if (!done[v]) decompose(v, cen); //decompose rest
    }
}

void solve() 
{
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) 
    {
        int u, v; 
        cin >> u >> v;
        
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_lca(1, 0);
    fillAncestor(n);
    decompose(1, 0);
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
    
    return 0;
}