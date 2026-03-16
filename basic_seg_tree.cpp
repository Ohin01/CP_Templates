#include<bits/stdc++.h>
using namespace std;

typedef long long   ll;
typedef vector<ll> vll;

struct SegTree
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

    void assign(int i, int v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] = v;;
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

int main(void)
{
    
}