#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
pair<int,int> t[N][18];
int a[N];

pair<int,int> combine(pair<int,int> A, pair<int,int> B) {
    vector<int> v = {A.first, A.second, B.first, B.second};
    sort(v.begin(), v.end(), greater<int>());

    int mx1 = v[0];
    int mx2 = -1;
    for (int x : v) {
        if (x != mx1) { mx2 = x; break; }
    }
    return {mx1, mx2};
}

void build(int n) {
    for (int i = 1; i <= n; ++i)
        t[i][0] = {a[i], -1};

    for (int k = 1; k < 18; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
            t[i][k] = combine(t[i][k - 1],
                              t[i + (1 << (k - 1))][k - 1]);
        }
    }
}

pair<int,int> query(int l, int r) {
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