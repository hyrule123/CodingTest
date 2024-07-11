#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset

/*복습 - 11049 행렬 곱셈 순서*/
#include <vector>
struct mat { int r, c; };
std::vector<mat> mats;

//dp[i][j]: i 행렬부터 j 행렬까지 곱했을 때 최소값
std::vector<std::vector<int>> dp;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	mats.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		std::cin >> mats[i].r >> mats[i].c;
	}

	dp.resize(N + 1, std::vector<int>(N + 1));

	for (int range = 1; range <= N; ++range) {
		for (int r = 1; r + range <= N; ++r) {
			int c = r + range;
			dp[r][c] = std::numeric_limits<int>::max();

			for (int pivot = r; pivot < c; ++pivot) {
				dp[r][c] = std::min(dp[r][c],
					dp[r][pivot] + dp[pivot + 1][c]

					//요게 핵심. 가운데 c가 pivot의 c임에 주의
					+ mats[r].r * mats[pivot].c * mats[c].c
				);
			}
		}
	}

	std::cout << dp[1][N];

	return 0;
}