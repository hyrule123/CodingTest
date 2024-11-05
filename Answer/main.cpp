#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

using uint = unsigned int;
//dp[i][j]: 일꾼이 i + 1명 일 중일때, 각자 담당하고 있는 작업(bit flag)
uint N, dp[21][1 << 21];
constexpr uint INF = -1;

uint get_memo(uint cur, uint flag) {
	if (dp[cur][flag] != INF) {
		return dp[cur][flag];
	}

	uint& ret = dp[cur][flag];

	//내가 i일을 담당할 경우, 일 i는 내가 해야 되므로
	for (uint i = 0; i < N; ++i) {
		//i일을 flag에서 제외했을 때 최대값을 구한다.(만약 일 i를 시키지 않았다면 계산 x)
		//ex)내가 0번일을 한다고 하면 111 -> 011 + 내가 i 일을 했을 때의 속도
		if (flag & (1 << i)) {
			ret = min(ret, get_memo(cur - 1, flag & ~(1 << i)) + get_memo(cur, 1 << i));
		}
	}

	return ret;
}

void solve() {
	cin >> N;
	memset(dp, -1, sizeof(uint) * 21 * (1ull << 21));
	for (uint i = 0; i < N; ++i) {
		for (uint j = 0; j < N; ++j) {
			cin >> dp[i][1ull << j];
		}
	}

	//N명이 모두 각자 하나씩 일을 맡을 경우에 대한 dp값을 구해서 출력
	cout << get_memo(N - 1, (1 << N) - 1);
}
