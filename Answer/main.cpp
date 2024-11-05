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

//개선판 - 코드 참고: https://www.acmicpc.net/source/86025722
using uint = unsigned int;
//dp[i]: [플래그값] 인원이 일할 때 필요한 업무량의 최소값
uint N, chart[21][21], dp[1 << 21];
constexpr uint INF = -1;

uint get_memo(uint cur, uint flag) {
	if (cur == INF) {
		return 0;
	}

	if (dp[flag] != INF) {
		return dp[flag];
	}

	uint& ret = dp[flag];

	//내가 i일을 담당할 경우, 일 i는 내가 해야 되므로
	for (uint i = 0; i < N; ++i) {
		//i일을 flag에서 제외했을 때 최대값을 구한다.(만약 일 i를 시키지 않았다면 계산 x)
		//ex)내가 0번일을 한다고 하면 111 -> 011 + 내가 i 일을 했을 때의 속도
		if (flag & (1 << i)) {
			ret = min(ret, get_memo(cur - 1, flag & ~(1 << i)) + chart[cur][i]);
		}
	}

	return ret;
}

void solve() {
	cin >> N;
	for (uint i = 0; i < N; ++i) {
		for (uint j = 0; j < N; ++j) {
			cin >> chart[i][j];
		}
	}

	memset(dp, -1, sizeof(uint) * (1ull << 21));
	//N명이 모두 각자 하나씩 일을 맡을 경우에 대한 dp값을 구해서 출력
	cout << get_memo(N - 1, (1 << N) - 1);
}
