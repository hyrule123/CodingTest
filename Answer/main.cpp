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
백준 11049 (행렬 곱셈 순서) [복습][DP]
재귀를 사용한 풀이(72ms)로, 예전에 풀었던 for문 반복 풀이(32ms)보다 느리다.
*/
#define ROW first
#define COL second
using uint = unsigned int;
using puu = pair<uint, uint>;
uint N;
puu mats[500];
uint dp[500][500];

uint DP_recursive(uint from, uint to) {
	if (dp[from][to] != 0xff'ff'ff'ff) {
		return dp[from][to];
	}

	//1, 2, 3 -> 1/23, 12/3
	//전부 해본다
	for (uint mid = from; mid < to; ++mid) {
		uint calc_counts = 
			DP_recursive(from, mid) + DP_recursive(mid + 1, to)
			//from ~ mid 행렬을 계산하는데 필요한 연산비용의 최소값과
			//mid + 1 ~ to 행렬을 만드는데 필요한 연산비용의 최소값을 더한뒤
			//두 행렬을 곱하는 비용을 추가한다.
			//cf. mats[mid].COL은 mats[mid + 1].ROW로 대체 가능
			+ mats[from].ROW * mats[mid].COL * mats[to].COL;
		dp[from][to] = min(dp[from][to], calc_counts);
	}

	return dp[from][to];
}

void solve() {
	memset(dp, -1, sizeof(dp));

	cin >> N;
	cin >> mats[0].ROW >> mats[0].COL;
	dp[0][0] = 0;
	for (uint i = 1; i < N; ++i) {
		cin >> mats[i].ROW >> mats[i].COL;
		dp[i - 1][i] = mats[i - 1].ROW * mats[i].ROW * mats[i].COL;

		dp[i][i] = 0;
	}

	cout << DP_recursive(0, N - 1);
}