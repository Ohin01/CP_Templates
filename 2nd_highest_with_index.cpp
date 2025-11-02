#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOG = 18;

struct Node {
    int val1, idx1;  // largest
    int val2, idx2;  // 2nd largest
};

Node t[N][LOG];
int a[N];

Node combine(Node A, Node B) {
    // Collect up to 4 candidates (value, index)
    vector<pair<int,int>> v = {
        {A.val1, A.idx1},
        {A.val2, A.idx2},
        {B.val1, B.idx1},
        {B.val2, B.idx2}
    };

    // Remove invalid entries (-1 index)
    v.erase(remove_if(v.begin(), v.end(),
                      [](auto &p){ return p.second == -1; }),
            v.end());

    // Sort by value descending
    sort(v.begin(), v.end(), [](auto &x, auto &y) {
        return x.first > y.first;
    });

    Node res = {-1, -1, -1, -1};
    if (!v.empty()) {
        res.val1 = v[0].first;
        res.idx1 = v[0].second;
    }
    // find 2nd distinct index
    for (auto &p : v) {
        if (p.second != res.idx1) {
            res.val2 = p.first;
            res.idx2 = p.second;
            break;
        }
    }
    return res;
}

void build(int n) {
    for (int i = 1; i <= n; ++i)
        t[i][0] = {a[i], i, -1, -1};

    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
            t[i][k] = combine(t[i][k - 1],
                              t[i + (1 << (k - 1))][k - 1]);
        }
    }
}

Node query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return combine(t[l][k], t[r - (1 << k) + 1][k]);
}

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