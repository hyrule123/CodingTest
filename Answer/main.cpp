#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset

/*
백준 1520 내리막 길 (복습)
*/
#include <vector>
//memo: 현재 위치에서 끝에 도달할 수 있는 경우의 수
struct cont { int val = std::numeric_limits<int>::max(), memo = -1; };
std::vector<std::vector<cont>> dp;
int N, M;
int SearchPath(int _r, int _c) {
	//도착했을 경우 1 반환
	if (_r == N && _c == M) { return 1; }

	//메모가 없으면(이 경로 처음 방문하면) 경로 계산
	if (dp[_r][_c].memo == -1) {
		dp[_r][_c].memo = 0;

		cont& cur = dp[_r][_c];

		//상하좌우
		if (dp[_r - 1][_c].val < cur.val) { cur.memo += SearchPath(_r - 1, _c); }
		if (dp[_r + 1][_c].val < cur.val) { cur.memo += SearchPath(_r + 1, _c); }
		if (dp[_r][_c - 1].val < cur.val) { cur.memo += SearchPath(_r, _c - 1); }
		if (dp[_r][_c + 1].val < cur.val) { cur.memo += SearchPath(_r, _c + 1); }
	}
	
	//메모가 있으면 이미 해당 위치에서 경로가 계산된 것이므로 그대로 반환
	return dp[_r][_c].memo;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M;
	dp.resize(N + 2, std::vector<cont>(M + 2));
	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= M; ++c) {
			std::cin >> dp[r][c].val;
		}
	}
	std::cout << SearchPath(1, 1);

	return 0;
}