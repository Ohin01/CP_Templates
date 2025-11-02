#include<bits/stdc++.h>
using namespace std;

typedef long long   ll;
typedef vector<ll> vll;

const ll INF = 9e18;

struct SegTree
{
    ll sz = 0;
    vll res;
    vll lazy;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
        lazy.assign(sz * 2, INF);
    }

    ll operation(ll a, ll b)
    {
        return a + b;
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == INF) return;

        res[x] = (rx - lx + 1) * lazy[x];

        if (lx != rx)
        {
            lazy[2 * x + 1] = lazy[x];
            lazy[2 * x + 2] = lazy[x];
        }

        lazy[x] = INF;
    }

    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = INF;

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

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy[x] = v;
            push(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    ll getRes(int l, int r, int x, int lx, int rx)
    {
        push(x, lx, rx);
        
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
    return 0;
}

