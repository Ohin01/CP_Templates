#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU 
{
    vector<ll> par, rnk, sz;
    ll c;

    struct State 
    {
        ll u, v;
        ll rnk_u, rnk_v;
        ll sz_v;
        ll prev_c;
    };
    vector<State> history; // history: stores changes for rollback

    DSU(ll n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) 
    {
        for (ll i = 1; i <= n; i++) par[i] = i;
    }

    ll find(ll i) 
    {
        while (par[i] != i) i = par[i];
        return i;
    }

    bool same(ll i, ll j) 
    {
        return find(i) == find(j);
    }

    ll get_size(ll i) 
    {
        return sz[find(i)];
    }

    ll count() 
    {
        return c; // connected components
    }

    void merge(ll i, ll j) 
    {
        i = find(i);
        j = find(j);

        if (i == j) 
        {
            history.push_back({-1, -1, -1, -1, -1, c}); // store previous state
            return;
        }

        if (rnk[i] > rnk[j]) swap(i, j);

        history.push_back({i, j, rnk[i], rnk[j], sz[j], c});

        par[i] = j;
        sz[j] += sz[i];
        c--;

        if (rnk[i] == rnk[j]) rnk[j]++;
    }

    void rollback() 
    {
        assert(!history.empty());
        auto s = history.back();
        history.pop_back();

        c = s.prev_c;

        if (s.u == -1) return; // nothing merged

        ll i = s.u, j = s.v;

        par[i] = i;
        rnk[i] = s.rnk_u;
        rnk[j] = s.rnk_v;
        sz[j] = s.sz_v;
    }

    int snapshot() 
    {
        return history.size();
    }

    void rollback_to(int snap) 
    {
        while ((int)history.size() > snap) 
        {
            rollback();
        }
    }
};