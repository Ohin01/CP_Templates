#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef pair<ll, ll>        pll;

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

vector<vector<pll>> dp(405, vector<pll>(405, {-1, -1}));
ll a[405];
ll n;

pll func(ll l, ll r)
{
    pll p = {-1, -1};

    if (dp[l][r] != p) return dp[l][r];

    if (l == r) return {0, a[l]};

    pll ans = {INF, INF};

    FOR(i, l, r)
    {
        pll cmp =  {func(l, i).ff + func(i + 1, r).ff + func(l, i).ss + func(i + 1, r).ss, func(l, i).ss + func(i + 1, r).ss};
        //cout << cmp.ff << " " << cmp.ss << endl;
        ans = min(ans, cmp);
    }

    return dp[l][r] = ans;
}

void solve()
{
    cin >> n;

    FOR(i, 1, n + 1)
    {
        cin >> a[i];
    }

    cout << func(1, n).ff << endl;


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