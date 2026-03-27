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
 
ll h[MAX];
ll dp[MAX];
 
void solve()
{
    ll n;
    cin >> n;
 
    FOR(i, 1, n + 1) cin >> h[i];
 
    FOR(i, 0, n + 1)
    dp[i] = 0;
 
    vll best;
    best.pb(0);
 
    FOR(i, 1, n + 1)
    {
        auto it = lower_bound(best.begin(), best.end(), h[i]);
 
        ll ind;
 
        if (it == best.end())
        {
            best.pb(h[i]);
            ind = best.size() - 1;
        }
 
        else
        {
            ind = it - best.begin();
            best[ind] = h[i];
        }
    }
 
    cout << best.size() - 1 << endl;
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