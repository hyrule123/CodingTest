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

int memo[41][2];

void solve() {
	memo[0][0] = 1;
	memo[1][1] = 1;

	//fib(2) = fib(1) + fib(0) -> dp[1] + dp[0]
	//fib(3) = fib(2) + fib(1)
	for (int i = 2; i <= 40; ++i) {
		memo[i][0] = memo[i - 1][0] + memo[i - 2][0];
		memo[i][1] = memo[i - 1][1] + memo[i - 2][1];
	}

	int TC; cin >> TC;
	while (TC--) {
		int input; cin >> input;
		cout << memo[input][0] << ' ' << memo[input][1] << '\n';
	}
}