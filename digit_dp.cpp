#include<bits/stdc++.h>
using namespace std;
 
typedef long long       ll;
 
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)
 
ll dp[11][20][2];
string s1, s2;
 
ll func(ll dig, ll ind, ll tight, string &s)
{
    if (dp[dig][ind][tight] != -1) return dp[dig][ind][tight];
 
    ll ans = 0;
 
    if (tight == 0)
    {
        FOR(i, 0, 10)
        {
            if (i == dig)
            continue;
 
            ans += func(i, ind + 1, 0, s);
        }
    }
 
    else
    {
        ll till = s[ind + 1] - '0';
 
        FOR(i, 0, till)
        {
            if (i == dig)
            continue;
 
            ans += func(i, ind + 1, 0, s);
        }
 
        if (till != dig)
        ans += func(till, ind + 1, 1, s);
 
    }
 
    return dp[dig][ind][tight] = ans;
}
 
void solve()
{
    ll n1, n2;
    cin >> n1 >> n2;
 
    if (n1 == 0 && n2 == 0) 
    {
        cout << 1 << endl;
        return;
    }
 
    ll ans1 = 0, ans2 = 0;
 
    if (n1 == 0 || n1 == 1)
    {
        s2 = to_string(n2);
 
        memset(dp, -1, sizeof(dp));
 
        FOR(i, 0, 10) dp[i][s2.size() - 1][0] = dp[i][s2.size() - 1][1] = 1;
 
        FOR(j, 0, s2.size())
        {
            if (j == 0)
            {
                FOR(i, 1, s2[j] - '0')
                {
                    ans2 += func(i, j, 0, s2);
                }
 
                ans2 += func(s2[0] - '0', 0, 1, s2);
                continue;
            }
 
            FOR(i, 1, 10)
            {
                ans2 += func(i, j, 0, s2);
            }
        }
 
        if (n1 == 0) cout << ans2 + 1 << endl;
        else cout << ans2 << endl;
        return;
    }
 
    n1--;
    s1 = to_string(n1);
    s2 = to_string(n2);
    //cin >> s1 >> s2;
 
    memset(dp, -1, sizeof(dp));
 
    FOR(i, 0, 10) dp[i][s1.size() - 1][0] = dp[i][s1.size() - 1][1] = 1;
 
    FOR(j, 0, s1.size())
    {
        if (j == 0)
        {
            FOR(i, 1, s1[j] - '0')
            {
                ans1 += func(i, j, 0, s1);
            }
 
            ans1 += func(s1[0] - '0', 0, 1, s1);
            continue;
        }
 
        FOR(i, 1, 10)
        {
            ans1 += func(i, j, 0, s1);
        }
    }
 
 
    //cout << dp[2][0][1] << endl;
 
    //cout << ++ans1 << endl;
 
    memset(dp, -1, sizeof(dp));
 
    FOR(i, 0, 10) dp[i][s2.size() - 1][0] = dp[i][s2.size() - 1][1] = 1;
 
    FOR(j, 0, s2.size())
    {
        if (j == 0)
        {
            FOR(i, 1, s2[j] - '0')
            {
                ans2 += func(i, j, 0, s2);
            }
 
            ans2 += func(s2[0] - '0', 0, 1, s2);
            continue;
        }
 
        FOR(i, 1, 10)
        {
            ans2 += func(i, j, 0, s2);
        }
    }
 
    //cout << ++ans2 << endl;
 
    cout << ans2 - ans1 << endl;
 
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