#include <iostream>
#include <vector>
using namespace std;

template <typename T> 
struct BIT2D 
{
	const int n, m;
	vector<vector<T>> bit;

	BIT2D(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}

	/** adds val to the point (r, c) */
	void add(int r, int c, T val) {
		for (; r <= n; r += r & -r) {
			for (int i = c; i <= m; i += i & -i) { bit[r][i] += val; }
		}
	}

	/** @returns sum of points with row in [1, r] and column in [1, c] */
	T rect_sum(int r, int c) {
		T sum = 0;
		for (; r > 0; r -= r & -r) {
			for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
		}
		return sum;
	}

	/** @returns sum of points with row in [r1, r2] and column in [c1, c2] */
	T rect_sum(int r1, int c1, int r2, int c2) {
		return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
		       rect_sum(r1 - 1, c1 - 1);
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	BIT2D<int> bit(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char c;
			cin >> c;
			if (c == '*') { bit.add(i, j, 1); }
		}
	}

	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int r, c;
			cin >> r >> c;
			r--, c--;
			if (bit.rect_sum(r, c, r, c) == 1) {
				bit.add(r, c, -1);
			} else {
				bit.add(r, c, 1);
			}
		} else if (type == 2) {
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			r1--, c1--, r2--, c2--;
			cout << bit.rect_sum(r1, c1, r2, c2) << '\n';
		}
	}
}