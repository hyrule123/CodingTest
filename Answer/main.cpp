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
	std::vector<uint> dp(N, 1);

	std::cin >> seq[0];
	uint max = 1;
	for (size_t i = 1; i < N; ++i) {
		std::cin >> seq[i];

		size_t prev = i - 1;
		if (seq[prev] == seq[i]) {
			dp[i] = dp[prev];
			continue;
		}

		for (size_t j = 0; j < i; ++j) {
			if (seq[j] < seq[i]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
			}
		}
		max = std::max(max, dp[i]);
	}

	std::cout << max;

	return 0;
}
