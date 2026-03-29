#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

struct Line 
{
    ll m, c;
    Line(ll _m = 0, ll _c = INF) : m(_m), c(_c) {}

    ll eval(ll x) const 
    {
        return (ll)((__int128)m * x + c);
    }
};

struct Node 
{
    Line line;
    Node *left, *right;
    Node(Line v)
    {
        line = v;
        left = right = NULL;
    }
};

struct LiChao 
{
    ll L, R;
    Node* root;

    LiChao(ll l, ll r) : L(l), R(r) 
    {
        root = new Node(Line()); // neutral line
    }

    void insert_line(Line nw, ll lx, ll rx, Node* node) 
    {
        ll mid = (lx + rx) >> 1;

        bool left = nw.eval(lx) < node->line.eval(lx);
        bool middle = nw.eval(mid) < node->line.eval(mid);

        if (middle) swap(nw, node->line);

        if (lx == rx) return;

        if (left != middle) 
        {
            if (!node->left) node->left = new Node(Line());
            insert_line(nw, lx, mid, node->left);
        } 
        else 
        {
            if (!node->right) node->right = new Node(Line());
            insert_line(nw, mid + 1, rx, node->right);
        }
    }

    void insert_segment(Line nw, ll ql, ll qr, ll lx, ll rx, Node* node) 
    {
        if (qr < lx || rx < ql) return;

        if (ql <= lx && rx <= qr) 
        {
            insert_line(nw, lx, rx, node);
            return;
        }

        ll mid = (lx + rx) >> 1;

        if (!node->left) node->left = new Node(Line());
        if (!node->right) node->right = new Node(Line());

        insert_segment(nw, ql, qr, lx, mid, node->left);
        insert_segment(nw, ql, qr, mid + 1, rx, node->right);
    }

    ll query_point(ll x, ll lx, ll rx, Node* node) 
    {
        if (!node) return INF;

        ll res = node->line.eval(x);

        if (lx == rx) return res;

        ll mid = (lx + rx) >> 1;

        if (x <= mid && node->left)
            return min(res, query_point(x, lx, mid, node->left));

        if (x > mid && node->right)
            return min(res, query_point(x, mid + 1, rx, node->right));

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. define x-range (VERY IMPORTANT)
    LiChao lc(-1e6, 1e6);

    // 2. add some lines: y = m*x + c
    lc.insert_line(Line(2, 3), lc.L, lc.R, lc.root);   // y = 2x + 3
    lc.insert_line(Line(-1, 10), lc.L, lc.R, lc.root); // y = -x + 10

    // 3. add line only on segment [l, r]
    lc.insert_segment(Line(5, 0), -5, 5, lc.L, lc.R, lc.root); // y = 5x in [-5,5]

    // 4. query some points
    for (int x = -5; x <= 5; x++) {
        cout << "x = " << x << " -> min y = "
             << lc.query_point(x, lc.L, lc.R, lc.root) << '\n';
    }

    return 0;
}