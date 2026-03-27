#include<bits/stdc++.h>
using namespace std;
 
typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
 
#define pb              push_back
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

void solve()
{
    ll n, m;
    cin >> n >> m;
 
    vll a(n + 1), b(m + 1);
 
    vvll dp(n + 1, vll(m + 1, 0));
 
    FOR(i, 1, n + 1) cin >> a[i];
    FOR(i, 1, m + 1) cin >> b[i];
 
    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            if (a[i] == b[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                
            }
 
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
 
    vll ans;
 
    cout << dp[n][m] << endl;
 
    int st = n, en = m;
 
    while (st > 0 && en > 0)
    {
        if (a[st] == b[en])
        {
            ans.pb(a[st]);
            st--;
            en--;
        }
 
        else
        {
            if (dp[st][en] == dp[st - 1][en]) st--;
            else en--;
        }
    }
 
    reverse(ans.begin(), ans.end());
 
    FOR(i, 0, ans.size()) cout << ans[i] << " ";
 
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