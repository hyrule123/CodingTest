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

//백준 17435 (합성함수와 쿼리) [LCA 기초지식]

int m, f[200001], Q;
int fn(int repeat, int x) {
	while (repeat--) {
		x = f[x];
	}
	return x;
}

void solve() {
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> f[i];
	}

	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		int n, x; cin >> n >> x;
		cout << fn(n, x) << '\n';
	}
}