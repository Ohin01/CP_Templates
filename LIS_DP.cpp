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
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)
 
const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
 
struct SegTree
{
    ll sz = 0;
    vll res;
 
    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
    }
 
    ll operation(ll a, ll b)
    {
        return (a + b) % MOD;
    }
 
    void build(vll &a, int x, int lx, int rx)
    {
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
 
    void assign(int i, ll v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] += v;;
            res[x] %= MOD;
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
 
ll dp[MAX];
 
void solve()
{
    ll n;
    cin >> n;
 
    vll h(n);
    vll b(n);
 
    map<ll, ll> comp;
    ll ind = 1;
 
    for (int i = 0; i < n; i++) 
    {
        cin >> h[i];
        b[i] = h[i];
    }
 
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
 
    FOR(i, 0, b.size())
    {
        auto it = comp.find(b[i]);
 
        if (it == comp.end())
        {
            comp[b[i]] = ind;
            ind++;
        }
    }
 
    SegTree st(ind + 10);
 
    FOR(i, 0, n)
    {
        ll sum = st.getRes(0, comp[h[i]] - 1, 0, 0, st.sz - 1);
        dp[i] = sum + 1;
        dp[i] %= MOD;
        st.assign(comp[h[i]], dp[i], 0, 0, st.sz - 1);
    }
 
    ll ans = 0;
 
    FOR(i, 0, ind + 1)
    {
        ans += st.getRes(i, i, 0, 0, st.sz - 1);
        ans %= MOD;
    }
 
    cout << ans << endl;
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