#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
 
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MOD = 1e9 + 7;

int dp[21][(1<<21)];
int a[21][21];

int n;

int func(int ind, int av)
{
    if (ind > n - 1) return 1;
    
    if (av == 0) return 0;
    
    if (dp[ind][av] != -1) return dp[ind][av];
    
    int ans = 0;
    
    FOR(i, 0, n)
    {
        if ((av & (1<<i)) != 0 && a[ind][i] == 1)
        {
            ans += func(ind + 1, (av ^ (1<<i)));
            ans %= MOD;
        }
    }
    
    return dp[ind][av] = ans;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    
    cin >> n;
    
    FOR(i, 0, n)
    {
        FOR(j, 0, n)
        {
            cin >> a[i][j];
        }
    }
    
    cout << func(0, (1<<n) - 1) % MOD << endl;;
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
