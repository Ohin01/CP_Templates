#include<bits/stdc++.h>
using namespace std;

typedef long long  ll;
typedef vector<ll> vll;

const int MX = 1e6 + 9; 
int root[MX];

struct PerSegTree
{
    struct Node
    {
        int left = 0;
        int right = 0;
        ll val = 0;
    };

    Node nodes[MX * 20];
    int id = 0;

    // vector<Node> nodes;
    // int id = 0;
    // int sz = 0;

    // PerSegTree(int n)
    // {
    //     sz = 1;
    //     while (sz < n) sz *= 2;
    //     nodes.assign(sz * 20, {0, 0, 0});
    // }

    int build(vll &a, int lx, int rx)
    {
        int cur = ++id;

        if (lx == rx)
        {
            nodes[cur].val = a[lx];
            return cur;
        }

        int mid = (lx + rx) / 2;

        nodes[cur].left = build(a, lx, mid);
        nodes[cur].right = build(a, mid + 1, rx);

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;

        return cur;
    }

    int update(int prev, int i, ll v, int lx, int rx)
    {
        int cur = ++id;

        nodes[cur] = nodes[prev];

        if (lx == rx)
        {
            nodes[cur].val += v;
            return cur;
        }

        int mid = (lx + rx) / 2;

        if (i <= mid) 
        {
            nodes[cur].left = update(nodes[cur].left, i, v, lx, mid);
        }

        else
        {
            nodes[cur].right = update(nodes[cur].right, i, v, mid + 1, rx);
        }

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;
        return cur;
    }

    ll getSum(int cur, int l, int r, int lx, int rx)
    {
        if (rx < l || r < lx)
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return nodes[cur].val;
        }

        int mid = (lx + rx) / 2;

        return getSum(nodes[cur].left, l, r, lx, mid) + getSum(nodes[cur].right, l, r, mid + 1, rx);
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