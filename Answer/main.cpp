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

int N, K;
int dp[1001][1001];	//dp[n][k] = 갯수 n개의 색상환에서 k개를 칠하는 방법의 수
constexpr int mod = 1'000'000'003;

void solve()
{
	cin >> N >> K;

	for (int i = 0; i <= N; ++i) {
		dp[i][0] = 1;
		dp[i][1] = i;//i개의 색상환에서 1개만 색칠하는 방법은 i개
	}

	for (int i = 2; i <= N; ++i) {
		for (int j = 2; j <= K; ++j) {
			//이번 색상 미사용: dp[i-1][j]
			//이번 색상 사용: dp[i-2][j-1](바로 전 색상은 칠해져있으면 안되므로 전전 색상의 경우의 수를 가져온다)
			dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % mod;
		}
	}

	//[N] 사용하는 경우: [1], [N-1] 사용 불가
	//[2] ~ [N - 2]범위를 칠하는 경우의 수와 같다. 
	//[1] ~ [N - 3] == (N - 3)개의 색상환에서 (K - 1)개를 칠하는 방법의 수
	//dp[N - 3][K - 1]
	
	//[N] 미사용: [1]의 사용 여부와 관계 없이 [N - 1][K]까지 색칠이 완료되어야 함
	//dp[N - 1][K]
	
	int ans = (dp[N - 1][K] + dp[N - 3][K - 1]) % mod;
	cout << ans;
}
