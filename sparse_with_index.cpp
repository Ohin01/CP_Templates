#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int a[N];
pair<int, int> t2[N][18]; // {value, index}

pair<int, int> combine(pair<int, int> L, pair<int, int> R) {
    int val = max(L.first, R.first);

    if (val == L.first && val == R.first)
        return {val, min(L.second, R.second)};
    else if (val == L.first)
        return L;
    else if (val == R.first)
        return R;
    else
        return {val, min(L.second, R.second)};
}

void build(int n) {
    for (int i = 1; i <= n; ++i)
        t2[i][0] = {a[i], i};
    for (int k = 1; k < 18; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
            t2[i][k] = combine(t2[i][k - 1], t2[i + (1 << (k - 1))][k - 1]);
        }
    }
}

pair<int, int> query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return combine(t2[l][k], t2[r - (1 << k) + 1][k]);
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