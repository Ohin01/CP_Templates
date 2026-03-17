#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;
typedef vector<vb>      vvb;
typedef pair<int, int>  pi;
typedef vector<pi>      vpi;
typedef pair<ll, ll>    pll;
typedef vector<pll>     vpll;

#define pb              push_back
#define ff              first
#define ss              second
#define index           find_by_order
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;

vb vis(MAX, false);
vi order;

void store_order(ll node, vvi &graph)
{
    vis[node] = true;

    for (auto child: graph[node])
    {
        if (vis[child]) continue;

        store_order(child, graph);
    }

    order.pb(node);
}

void dfs(ll node, vi &comp, vb &used, vvi &inv)
{
    used[node] = true;
    comp.pb(node);

    for (auto child: inv[node])
    {
        if (used[child]) continue;

        dfs(child, comp, used, inv);
    }
}

vvi kosaraju(vvi &inv)
{
    vvi ans;

    vb used(MAX, false);

    reverse(order.begin(), order.end()); //find correct dfs order

    FOR(i, 0, order.size())
    {
        if (used[order[i]])
        continue;

        vi temp;

        dfs(order[i], temp, used, inv);

        ans.pb(temp);
    }

    return ans;
}

vll dp(MAX, -1);

ll find_ans(ll node, vvi &g, vll &coins)
{
    if (dp[node] != -1) return dp[node];

    ll mx = coins[node];

    for (auto ch: g[node])
    {
        mx = max(mx, coins[node] + find_ans(ch, g, coins));
    }

    return dp[node] = mx;
}

void solve()
{
    ll n, m;
    cin >> n >> m;

    vll c(n + 1);

    FOR(i, 1, n + 1) cin >> c[i];

    vvi graph(n + 1);
    vvi inv(n + 1);

    FOR(i, 0, m)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].pb(v);
        inv[v].pb(u);
    }

    FOR(i, 1, n + 1)
    {
        if (!vis[i])
        {
            store_order(i, graph);
        }
    }

    vvi scc = kosaraju(inv);
    int sz = scc.size();

    vll coins(sz + 1);

    vi ans(n + 1);

    FOR(i, 0, scc.size())
    {
        for (auto node: scc[i])
        {
            ans[node] = i + 1;
            coins[ans[node]] += c[node];
        }
    }

    vvi cond(sz + 1); //condensation

    set<pi> used;

    FOR(i, 1, n + 1)
    {
        for (auto ch: graph[i])
        {
            if (ans[i] == ans[ch]) continue;
            auto it = used.find({ans[i], ans[ch]});

            if (it == used.end())
            {
                cond[ans[i]].pb(ans[ch]);
                used.insert({ans[i], ans[ch]});
            }
        }
    }

    ll mx = -1;

    FOR(i, 1, sz + 1)
    {
        mx = max(mx, find_ans(i, cond, coins));
    }

    cout << mx << endl;
    
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