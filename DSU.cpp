#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU 
{
    vector<ll> par, rnk, sz;
    ll c;
    DSU(ll n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
      for (ll i = 1; i <= n; ++i) par[i] = i;
    }
    ll find(ll i) {
      return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(ll i, ll j) {
      return find(i) == find(j);
    }
    ll get_size(ll i) {
      return sz[find(i)];
    }
    ll count() {
      return c;    //connected components
    }
    void merge(ll i, ll j) {
      if ((i = find(i)) == (j = find(j))) return;
      else --c;
      if (rnk[i] > rnk[j]) swap(i, j);
      par[i] = j;
      sz[j] += sz[i];
      if (rnk[i] == rnk[j]) rnk[j]++;
    }
};