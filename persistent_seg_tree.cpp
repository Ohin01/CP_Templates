#include<bits/stdc++.h>
using namespace std;

typedef long long  ll;
typedef vector<ll> vll;

const int MX = 1e6 + 9; 
int root[MX];

struct Node
{
    int left = 0;
    int right = 0;
    ll val = 0;
};

Node nodes[MX * 40];

struct PerSegTree
{
    int id = 0;

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
            nodes[cur].left = update(nodes[cur].left, i, v, lx, mid);
        else
            nodes[cur].right = update(nodes[cur].right, i, v, mid + 1, rx);

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

    ll kth(int u, int v, int k, int lx, int rx, vector<ll> &sortedA) //0-based
    {
        if(lx == rx) return sortedA[lx];

        int mid = (lx + rx) / 2;

        int cnt = nodes[nodes[v].left].val - nodes[nodes[u].left].val;

        if(k <= cnt) 
            return kth(nodes[u].left, nodes[v].left, k, lx, mid, sortedA);
        else
            return kth(nodes[u].right, nodes[v].right, k - cnt, mid + 1, rx, sortedA);
    }
};


void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];

    vll sortedA; //compress A here
    ll sz = sortedA.size();

    PerSegTree pst;
    vll empty(sz, 0);
    root[0] = pst.build(empty, 0, sz - 1);

    for(int i = 0; i < n; i++)
    {
        ll val; //compress A[i]
        root[i + 1] = pst.update(root[i], val, 1, 0, sz - 1);
    }
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