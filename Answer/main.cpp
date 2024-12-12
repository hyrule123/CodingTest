#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}
/*
백준 2042 (구간 합 구하기) [세그먼트 트리]
https://codeforces.com/blog/entry/18051
*/
using ll = int64_t;
const ll N = (ll)1e6;  // limit for array size
ll n, m, k;  // array size
ll t[2 * N];

void build() {  // build the tree
	for (ll i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(ll p, ll value) {  // set value at position p
	for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

ll query(ll l, ll r) {  // sum on interval [l, r)
	ll res = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += t[l++];
		if (r & 1) res += t[--r];
	}
	return res;
}


void solve() {
	cin >> n >> m >> k;
	for (ll i = 0; i < n; ++i) {
		cin >> t[n + i];
	}
	build();

	for (ll i = 0; i < m + k; ++i) {
		ll a, b, c; cin >> a >> b >> c;
		switch (a)
		{
		case 1:
			modify(b - 1, c);
			break;
		case 2:
			cout << query(b - 1, c) << '\n';
			break;
		default:
			break;
		}
	}
}