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
백준 1009 (분산처리)
a^b = a * a * ... * a (총 b회 곱) -> mod 연산 적용 가능

*/

void solve() {
	int T; cin >> T;
	while (T--) {
		int a, b; cin >> a >> b;

		a %= 10;
		int ans = 1;
		for (int i = 1; i <= b; ++i) {
			ans = (ans * a) % 10;
		}

		if (ans == 0) { ans = 10; }

		cout << ans << '\n';
	}
}