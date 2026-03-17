#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;

#define pb              push_back
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;

struct FenTree // 1-based currently
{
    vector<ll> sum;
    int sz;

    void init(int n)
    {
        sum.assign(n + 1, 0);
        sz = n;
    }

    void update(int ind, ll x)
    {
        while (ind <= sz) //ind < sz
        {
            sum[ind] += x;
            ind += (ind & (-ind)); //ind |= (ind + 1);
        }
    }

    ll query(int ind)
    {
        ll ans = 0;
        while (ind > 0) //ind >= 0
        {
            ans += sum[ind];
            ind -= (ind & (-ind)); //ind = (ind & (ind + 1)) - 1;
        }
        return ans;
    }

    ll query(int l, int r)
    {
        //if (l == 0) return query(r);
        return query(r) - query(l - 1);
    }

    int lowerBound(int v)
    {
        int pos = 0;
        ll tot = 0;

        FORR(i, LOGN, 0)
        {
            if (pos + (1<<i) <= sz && tot + sum[pos + (1<<i)] < v)
            {
                tot += sum[pos + (1<<i)];
                pos += (1<<i);
            }
        }
        return pos + 1; //pos gives the highest lower number
    }
};



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