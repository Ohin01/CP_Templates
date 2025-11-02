#include<bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
typedef long long ll;
typedef vector<ll> vll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

vector<ll> spf(MX);

void sieve()
{
    for (int i = 0; i < MX; i++) spf[i] = i;

    for (int i = 2; i * i < MX; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MX; j += i) {
                if (spf[j]== j)
                    spf[j] = i;
            }
        }
    }
}

vector<ll> getPrimeFactors(int x)
{
    vector<ll> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}

vector<ll> getAllFactors(int x)
{
    vll prime, power;

    while (x != 1) {
        int p = spf[x];
        int cnt = 0;
        while (x % p == 0) {
            cnt++;
            x /= p;
        }
        prime.push_back(p);
        power.push_back(cnt);
    }

    vll ans = {1};
    FOR(i, 0, prime.size()) {
        vll temp;
        ll val = 1;
        for (int j = 1; j <= power[i]; j++) {
            val *= prime[i];
            for (auto d : ans)
                temp.push_back(d * val);
        }
        ans.insert(ans.end(), temp.begin(), temp.end());
    }
    return ans;
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