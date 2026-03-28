#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

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

struct SegTree
{
    ll sz = 0;
    vll res;
    vll lazy;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
        lazy.assign(sz * 2, 0);
    }

    ll operation(ll a, ll b)
    {
        return a + b;
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == 0) return;

        res[x] += (rx - lx + 1) * lazy[x];

        if (lx != rx)
        {
            lazy[2 * x + 1] += lazy[x];
            lazy[2 * x + 2] += lazy[x];
        }

        lazy[x] = 0;
    }

    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = 0;

        if (lx == rx)
        {
            if (lx < (int)a.size())
            res[x] = a[lx];

            else
            res[x] = 0;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy[x] += v;
            push(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    ll getRes(int l, int r, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) 
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return operation(getRes(l, r, 2 * x + 1, lx, mid), getRes(l, r, 2 * x + 2, mid + 1, rx));
    }
};

vll c(MAX * 2);
vll sum(MAX * 2);
int ans = -1;
int n;
int timer = 1;
ll euler[MAX * 2];
ll intime[MAX * 2];
ll outtime[MAX * 2];

void dfs(int node, int par, vvll &g)
{
    intime[node] = timer; 
    sum[node] += c[node];
    euler[timer++] = node;

    for(auto ch: g[node])
    {
        if (ch == par) continue;

        sum[ch] += sum[node];

        dfs(ch, node, g);
    }

    outtime[node] = timer;
    euler[timer++] = node;
}

void solve()
{
    cin >> n;

    int q;
    cin >> q;

    FOR(i, 1, n + 1) cin >> c[i];

    vvll g(n + 1);
    
    FOR(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0, g);

    SegTree st(timer + 1);

    vll bb;
    bb.pb(0);

    FOR(i, 1, timer)
    {
        bb.pb(sum[euler[i]]);
    }


    st.build(bb, 0, 0, st.sz - 1);

    while (q--)
    {
        ll t;
        cin >> t;

        if (t == 1)
        {
            ll node, val;
            cin >> node >> val;

            ll diff = val - c[node];
            c[node] = val;
            
            st.update(intime[node], outtime[node], diff, 0, 0, st.sz - 1);
        }

        else
        {
            ll node;
            cin >> node;

            cout << st.getRes(intime[node], intime[node], 0, 0, st.sz - 1) << endl;
        }
    }
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