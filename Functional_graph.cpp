#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;
typedef vector<vb>      vvb;
typedef pair<int, int>  pi;
typedef vector<pi>      vpi;
typedef pair<ll, ll>    pll;
typedef vector<pll>     vpll;

#define pb              push_back
#define ff              first
#define ss              second
#define index           find_by_order
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)
 
const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;

int nxt[MAX];
int state[MAX];
vi color(MAX, -1);
int id = 1;

void dfs(int node)
{
    state[node] = 1;

    int v = nxt[node];

    if (state[v] == 0)
    {
        dfs(v);
    }

    else if (state[v] == 1)
    {
        int start = v;
        int cur = start;

        do {
            color[cur] = id;
            cur = nxt[cur];
        } while (cur != start);

        id++;
    }

    state[node] = 2;
}

void solve()
{
    ll n;
    cin >> n;

    vvi rev(n + 1);

    FOR(i, 1, n + 1)
    {
        cin >> nxt[i];
        rev[nxt[i]].pb(i);
    }

    FOR(i, 1, n + 1)
    {
        if (state[i] == 0)
        dfs(i);
    }

    queue<int> q;
    vi dist(n + 1, -1);
    vi sz(id + 1);

    FOR(i, 1, n + 1)
    {
        if (color[i] != -1)
        {
            sz[color[i]]++;
            q.push(i);
            dist[i] = 0;
        }
    }

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (auto ch: rev[node])
        {
            if (dist[ch] == -1)
            {
                dist[ch] = dist[node] + 1;
                color[ch] = color[node];
                q.push(ch);
            }
        }
    }

    FOR(i, 1, n + 1)
    {
        cout << sz[color[i]] + dist[i] << " ";
    } cout << endl;




}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}