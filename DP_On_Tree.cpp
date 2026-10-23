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

ll downDP[MAX];
ll upDp[MAX];
ll p[MAX];

void dfs(int node, int par, vvi &g)
{
    p[node] = par;

    for (auto ch: g[node])
    {
        if (ch == par) continue;

        dfs(ch, node, g);

        downDP[node] = max(downDP[node], 1 + downDP[ch]); 
    }
}

void dfs2(int node, int par, vvi &g)
{
    vll childs;

    for (auto ch: g[node]){
        if (ch == par) continue;
        childs.pb(ch);
    }

    ll sz = childs.size();
    if (sz == 0) return;

    vll val(sz), suf(sz), pref(sz);

    FOR(i, 0, sz) val[i] = downDP[childs[i]] + 1;

    suf[sz - 1] = val[sz - 1]; pref[0] = val[0];

    FOR(i, 1, sz) pref[i] = max(val[i], pref[i - 1]);
    FORR(i, sz - 2, 0) suf[i] = max(val[i], suf[i + 1]); 

    FOR(i, 0, sz){
        ll mx = upDp[node];

        i == 0?  : mx = max(mx, pref[i - 1]);
        i == sz - 1? : mx = max(mx, suf[i + 1]);

        upDp[childs[i]] = max(upDp[childs[i]], 1 + mx);

        dfs2(childs[i], node, g);
    }
}


void solve()
{
    ll n;
    cin >> n;

    vvi g(n + 1);

    FOR(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0, g);
    dfs2(1, 0, g);
    
    FOR(i, 1, n + 1) cout << max(downDP[i], upDp[i]) << " ";
    cout << endl;
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