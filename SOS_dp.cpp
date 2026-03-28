#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int n = 3;           // number of bits
    int N = 1 << n;      // total masks
    vector<int> A(N), f(N);

    // Example values
    A[0] = 1; A[1] = 2; A[2] = 3; A[3] = 4;
    A[4] = 5; A[5] = 6; A[6] = 7; A[7] = 8;

    // 1. Subset DP - Pull
    // f[mask] = sum of A[sub] for all sub ⊆ mask
    f = A;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < N; mask++) {
            if (mask & (1 << i)) {
                f[mask] += f[mask ^ (1 << i)];
            }
        }
    }
    cout << "Subset Pull:\n";
    for(int mask = 0; mask < N; mask++) cout << f[mask] << " "; 
    cout << "\n\n";

    // 2. Subset DP - Push
    // f[mask] = sum of A[sub] for all sub ⊆ mask
    f = A;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < N; mask++) {
            if (!(mask & (1 << i))) {
                f[mask | (1 << i)] += f[mask];
            }
        }
    }
    cout << "Subset Push:\n";
    for(int mask = 0; mask < N; mask++) cout << f[mask] << " "; 
    cout << "\n\n";

    // 3. Superset DP - Pull
    // f[mask] = sum of A[super] for all super ⊇ mask
    f = A;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < N; mask++) {
            if (!(mask & (1 << i))) {
                f[mask] += f[mask | (1 << i)];
            }
        }
    }
    cout << "Superset Pull:\n";
    for(int mask = 0; mask < N; mask++) cout << f[mask] << " "; 
    cout << "\n\n";

    // 4. Superset DP - Push
    // f[mask] = sum of A[super] for all super ⊇ mask
    f = A;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < N; mask++) {
            if (mask & (1 << i)) {
                f[mask ^ (1 << i)] += f[mask];
            }
        }
    }
    cout << "Superset Push:\n";
    for(int mask = 0; mask < N; mask++) cout << f[mask] << " "; 
    cout << "\n";

    return 0;
}