#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, q, a[N];
multiset<int> seg[4 * N + 5];

void build(int node, int l, int r)
{
    if (l == r)
    {
        seg[node].insert(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);

    seg[node].insert(seg[node * 2].begin(), seg[node * 2].end());
    seg[node].insert(seg[node * 2 + 1].begin(), seg[node * 2 + 1].end());
}

void edit(int idx, int val, int x, int lx, int rx)
{
    auto it = seg[x].find(a[idx]);
    if (it != seg[x].end()) seg[x].erase(it);

    seg[x].insert(val);

    if (lx == rx) return;

    int mid = (lx + rx) / 2;
    if (idx <= mid) edit(idx, val, x * 2, lx, mid);
    else edit(idx, val, x * 2 + 1, mid + 1, rx);
}

int query(int l, int r, int v, int x, int lx, int rx)
{
    if (rx < l || lx > r) return INT_MAX;

    if (lx >= l && rx <= r)
    {
        auto it = seg[x].lower_bound(v);
        if (it == seg[x].end()) return INT_MAX;
        return *it;
    }

    int mid = (lx + rx) / 2;
    return min(query(l, r, v, x * 2, lx, mid), query(l, r, v, x * 2 + 1, mid + 1, rx));
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build(1, 1, n);

    while (q--)
    {
        bool t;
        cin >> t;

        if (!t)
        {
            int idx, val;
            cin >> idx >> val;

            edit(idx, val, 1, 1, n);

            a[idx] = val;
        }
        else
        {
            int l, r, x;
            cin >> l >> r >> x;

            int y = query(l, r, x, 1, 1, n);

            if (y == INT_MAX)
                cout << -1 << '\n';
            else
                cout << y << '\n';
        }
    }

    return 0;
}