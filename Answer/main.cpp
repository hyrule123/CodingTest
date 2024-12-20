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
백준 11047 (동전 0) [복습][그리디]
*/
int N, K, coin_values[1'000'000];
void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		cin >> coin_values[i];
	}

	int ans = 0;
	for (int i = N - 1; i >= 0; --i) {
		int coins = K / coin_values[i];
		K -= coins * coin_values[i];
		ans += coins;

		if (K == 0) { break; }
	}

	cout << ans;
}