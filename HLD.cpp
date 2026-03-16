#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MAX = 2e5 + 5;
const int LOGN = 20;
const ll INF = 1e18 + 10;

struct SegTree
{
    ll sz = 0;
    vll res;

    void init(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, -INF);
    }

    ll operation(ll a, ll b)
    {
        return max(a, b);
    }

    void build(vll &a, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            if (lx < (int)a.size())
            res[x] = a[lx];

            else
            res[x] = -INF;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    void assign(int i, int v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] = v;;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) assign(i, v, 2 * x + 1, lx, mid);
        else assign(i, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    ll getRes(int l, int r, int x, int lx, int rx)
    {
        if (r < lx || rx < l) 
        {
            return -INF;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return operation(getRes(l, r, 2 * x + 1, lx, mid), getRes(l, r, 2 * x + 2, mid + 1, rx));
    }
};

SegTree t;

vector<int> g[MAX];
int par[MAX][LOGN + 1], depth[MAX], sz[MAX];
int T = 0, head[MAX], st[MAX], en[MAX];

void dfs(int node, int p = 0) 
{
    par[node][0] = p;
    sz[node] = 1;

    if (p != 0) g[node].erase(find(g[node].begin(), g[node].end(), p)); //erase the parent

    for (auto &ch: g[node])
    {
        if (ch == p) continue;
        
        depth[ch] = depth[node] + 1;
        dfs(ch, node);
        sz[node] += sz[ch];

        if(sz[ch] > sz[g[node][0]]) swap(ch, g[node][0]); //heavy child is always the first child
    }
}

void fillAncestor(int n)
{
    FOR(i, 1, LOGN)
    {
        FOR(j, 1, n + 1)
        {
            if (par[j][i - 1] != 0)
            par[j][i] = par[ par[j][i - 1] ][i - 1];

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

void dfs_hld(int node) 
{
    st[node] = ++T;

    for (auto ch: g[node]) 
    {
        if (ch == g[node][0]) head[ch] = head[node]; //head means top of the heavy chain
        else head[ch] = ch;
       
        dfs_hld(ch);
    }

    en[node] = T;
}

int query_up(int u, int v) //v is lca
{
    ll ans = -INF;

    while(head[u] != head[v]) //untill u and v are in the same heavy path
    {
        ans = max(ans, t.getRes(st[head[u]], st[u], 0, 0, t.sz - 1));
        u = par[head[u]][0];
    }

    ans = max(ans, t.getRes(st[v], st[u], 0, 0, t.sz - 1));
    return ans;
}

int query(int u, int v) 
{
    int lca = LCA(u, v);
    int ans = query_up(u, lca);

    if (v != lca) ans = max(ans, query_up(v, kthAncestor(v, depth[v] - depth[lca] - 1))); //dont include lca
    return ans;
}

int32_t main() 
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

    dfs(1);
    fillAncestor(n);
    head[1] = 1;
    dfs_hld(1);

    t.init(n + 1);
}