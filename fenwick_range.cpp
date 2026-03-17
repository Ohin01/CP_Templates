#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

typedef long long ll;

struct BIT 
{
    ll M[N], A[N];

    BIT() 
    {
        memset(M, 0, sizeof M);
        memset(A, 0, sizeof A);
    }

    void update(int i, ll mul, ll add) 
    {
        while (i < N) 
        {
            M[i] += mul;
            A[i] += add;
            i += i & -i;
        }
    }

    void range_update(int l, int r, ll x) 
    {
        update(l, x, -x * (l - 1));
        update(r + 1, -x, x * r);
    }

    ll query(int i) 
    {
        ll mul = 0, add = 0;
        int st = i;
        while (i > 0) 
        {
            mul += M[i];
            add += A[i];
            i -= i & -i;
        }
        return mul * st + add;
    }

    ll query(int l, int r) 
    {
        return query(r) - query(l - 1);
    }
};

int32_t main() 
{
    
}