#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef vector<int>     vi;

const int MAX = 2e5 + 5;

struct Mobius 
{
    vi mu;
    vi min_prime;
    vi cnt;
    ll coprime;

    Mobius(int limit = MAX) 
    {
        mu.resize(limit + 1);
        min_prime.resize(limit + 1, 0);
        cnt.resize(limit + 1, 0);
        coprime = 0;

        mu[1] = 1;
        vi primes;
        for (int i = 2; i <= limit; ++i) 
        {
            if (min_prime[i] == 0) 
            {
                min_prime[i] = i;
                primes.push_back(i);
                mu[i] = -1;
            }
            for (int p : primes) 
            {
                if (p > min_prime[i] || (ll)i * p > limit) break;
                min_prime[i * p] = p;

                if (min_prime[i] == p) mu[i * p] = 0;
                else mu[i * p] = -mu[i];
            }
        }
    }

    template<typename Func>
    void for_each_divisor(int x, Func callback) 
    {
        static vector<pair<int, int>> prime_factors;
        prime_factors.clear();
        int temp = x;
        while (temp > 1) {
            int p = min_prime[temp];
            int count = 0;
            while (temp % p == 0) { temp /= p; count++; }
            prime_factors.push_back({p, count});
        }

        auto dfs = [&](auto&& self, int idx, int current_divisor) -> void {
            if (idx == prime_factors.size()) {
                callback(current_divisor);
                return;
            }
            int p = prime_factors[idx].first;
            int exponent = prime_factors[idx].second;
            int p_pow = 1;
            for (int i = 0; i <= exponent; ++i) {
                self(self, idx + 1, current_divisor * p_pow);
                p_pow *= p;
            }
        };
        dfs(dfs, 0, 1);
    }

    void add(int x) 
    {
        if (x >= cnt.size()) return;
        for_each_divisor(x, [&](int d) {
            if (mu[d] == 0) return;
            coprime += (ll)mu[d] * cnt[d];
            cnt[d]++;
        });
    }

    void remove(int x) 
    {
        if (x >= cnt.size()) return;
        for_each_divisor(x, [&](int d) {
            if (mu[d] == 0) return;
            cnt[d]--;
            coprime -= (ll)mu[d] * cnt[d];
        });
    }

    void build(const vi& nums) 
    {
        fill(cnt.begin(), cnt.end(), 0);
        coprime = 0;
        vi f(MAX, 0);
        for (int x : nums) {
            if (x < MAX) f[x]++;
        }
        for (int i = 1; i < MAX; ++i) {
            for (int j = i; j < MAX; j += i) {
                cnt[i] += f[j];
            }
        }
        for (int i = 1; i < MAX; ++i) {
            if (mu[i] == 0 || cnt[i] < 2) continue;
            ll pairs = (ll)cnt[i] * (cnt[i] - 1) / 2;
            if (mu[i] == 1) coprime += pairs;
            else coprime -= pairs;
        }
    }

    ll get_coprime_pairs() const {
        return coprime;
    }

    ll get_pairs_with_gcd(int g) {
        ll ans = 0;
        for (int i = g; i < cnt.size(); i += g) {
            ans += (ll)mu[i / g] * ((ll)cnt[i] * (cnt[i] - 1) / 2);
        }
        return ans;
    }
};

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

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}