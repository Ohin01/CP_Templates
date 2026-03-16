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

vll graph[MAX];
vvll par(MAX, vll(20, 0));
vll depth(MAX, 0);

void dfs(ll node, ll parent)
{
    par[node][0] = parent;

    for (auto child: graph[node])
    {
        if (child == parent) continue; 
        depth[child] = depth[node] + 1;
        dfs(child, node);
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

void solve()
{
    
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}