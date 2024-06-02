#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint = unsigned int;

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	size_t N{}; std::cin >> N;
	std::vector<uint> seq(N);
	for (size_t i = 0; i < N; ++i) {
		std::cin >> seq[i];
	}

	struct length { uint fromLeft, fromRight; };
	std::vector<length> dp(N, { 1u, 1u });

	for (size_t left = 0; left < N; ++left) {
		//왼쪽에서 오른쪽으로
		for (size_t j = 0; j < left; ++j) {
			if (seq[j] < seq[left]) {
				dp[left].fromLeft = std::max(dp[left].fromLeft, dp[j].fromLeft + 1);
			}
		}

		//오른쪽에서 왼쪽으로
		size_t right = N - left - 1;
		for (size_t j = N - 1; j > right; --j) {
			if (seq[right] > seq[j]) {
				dp[right].fromRight = std::max(dp[right].fromRight, dp[j].fromRight + 1);
			}
		}
	}

	//left + right가 최대가 되는 부분을 구해준다.(둘다 각각 최소값 1) { 1 }의 max = 2 -> 나중에 1 빼줘야함
	uint max = 2;
	for (size_t i = 0; i < N; ++i) {
		max = std::max(max, dp[i].fromLeft + dp[i].fromRight);
	}
	--max;
	std::cout << max;

	return 0;
}
