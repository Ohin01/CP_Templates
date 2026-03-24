#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const ll INF = 9e18;
const int MAX = 2e5 + 5;

struct ISegTree
{
    ll sz = 0;
    vll res;

    void init(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
    }

    ll operation(ll a, ll b)
    {
        return a + b;
    }

    // Iterative build: Fill leaves then compute parents
    void build(vll &a, int x = 0, int lx = 0, int rx = 0)
    {
        for (int i = 0; i < (int)a.size(); i++) {
            res[sz + i] = a[i];
        }
        for (int i = sz - 1; i >= 1; i--) {
            res[i] = operation(res[2 * i], res[2 * i + 1]);
        }
    }

    // Iterative assign: Update leaf and walk up to the root
    void assign(int i, ll v, int x = 0, int lx = 0, int rx = 0)
    {
        int cur = i + sz;
        res[cur] = v;
        while (cur > 1) {
            cur /= 2;
            res[cur] = operation(res[2 * cur], res[2 * cur + 1]);
        }
    }

    // Iterative getRes: Query range [l, r]
    ll getRes(int l, int r, int x = 0, int lx = 0, int rx = 0)
    {
        ll ans = 0;
        l += sz;
        r += sz;
        
        while (l <= r) {
            if (l % 2 == 1) ans = operation(ans, res[l++]);
            if (r % 2 == 0) ans = operation(ans, res[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

int main(void)
{
    
}