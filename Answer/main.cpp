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

//마지막 집을 고정시키고 
constexpr int r = 0, g = 1, b = 2, INF = 987654321;
int N;
int dp[1001][3], costs[1001][3];

void solve()
{
	cin >> N;

	for (int i = 1; i <= N; ++i) {
		cin >> costs[i][r] >> costs[i][g] >> costs[i][b];
	}

	int ans = INF;
	for (int start = 0; start < 3; ++start) {
		memset(dp, 0, sizeof(dp));

		//시작점을 하나로 고정
		for (int i = 0; i < 3; ++i) {
			if (start == i) {
				dp[1][i] = costs[1][start];
			}
			else {
				dp[1][i] = INF;
			}
		}

		for (int i = 2; i <= N; ++i) {
			dp[i][r] = min(dp[i - 1][g], dp[i - 1][b]) + costs[i][r];
			dp[i][g] = min(dp[i - 1][r], dp[i - 1][b]) + costs[i][g];
			dp[i][b] = min(dp[i - 1][r], dp[i - 1][g]) + costs[i][b];
		}

		for (int end = 0; end < 3; ++end) {
			//시작점과 동일하게 끝난 값은 무의미
			if (start == end) { continue; }
			ans = min(ans, dp[N][end]);
		}
	}

	cout << ans;
}
