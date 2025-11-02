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
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)
 
const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;

vb vis(MAX, false);
vvll graph(MAX);
vvll inv(MAX);
vll order;

void store_order(ll node)
{
    vis[node] = true;

    for (auto child: graph[node])
    {
        if (vis[child]) continue;

        store_order(child);
    }

    order.pb(node);
}

void dfs(ll node, vll &comp, vb &used)
{
    used[node] = true;
    comp.pb(node);

    for (auto child: inv[node])
    {
        if (used[child]) continue;

        dfs(child, comp, used);
    }
}

vvll kosaraju()
{
    vvll ans;

    vb used(MAX, false);

    reverse(order.begin(), order.end());

    FOR(i, 0, order.size())
    {
        if (used[order[i]])
        continue;

        vll temp;

        dfs(order[i], temp, used);

        ans.pb(temp);
    }

    return ans;
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