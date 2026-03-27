#include<bits/stdc++.h>
using namespace std;
 
typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
 
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)
  
ll dp[5005][5005];
 
void solve()
{
    string s1, s2;
    cin >> s1 >> s2;
 
    s1 = 'x' + s1;
    s2 = 'x' + s2;
 
    FOR(i, 0, s2.size()) dp[i][0] = i;
 
    FOR(j, 1, s1.size())
    {
        if (s1[j] == s2[1])
        {
            dp[1][j] = min(dp[1][j - 1] + 1, j - 1);
        }
 
        else
        {
            dp[1][j] = min(dp[1][j - 1] + 1, j);
        }
    }
 
 
 
    FOR(i, 2, s2.size())
    {
        FOR(j, 1, s1.size())
        {
            if (s2[i] == s1[j])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
 
            else
            {
                dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
            }
        }
    }
 
    cout << dp[s2.size() - 1][s1.size() - 1] << endl;
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