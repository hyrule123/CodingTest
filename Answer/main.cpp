#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
struct mat { int r, c; };
int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	std::vector<mat> input(N);
	std::vector<std::vector<int>> dp(N, std::vector<int>(N));
	std::cin >> input[0].r >> input[0].c;
	for (int i = 1; i < N; ++i) {
		std::cin >> input[i].r >> input[i].c;
	}

	for (int range = 1; range < N; ++range) {
		for (int r = 0; r + range < N; ++r) {
			int c = r + range;
			dp[r][c] = std::numeric_limits<int>::max();

			for (int pivot = r; pivot < c; ++pivot) {
				dp[r][c] = std::min(dp[r][c],
					dp[r][pivot] + dp[pivot + 1][c]

					//이번 dp 경우의 수의 연산 횟수
					+ input[r].r * input[pivot].c * input[c].c
				);
			}
		}
	}
	std::cout << dp[0][N - 1];

	return 0;
}