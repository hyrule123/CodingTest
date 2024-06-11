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

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	int N, M; std::cin >> N >> M;

	std::vector<int> prevs(M);
	int prevIdx = 0;
	std::cin >> prevs[0];
	int sum = prevs[0];
	for (int i = 1; i < M; ++i) {
		std::cin >> prevs[i];
		sum += prevs[i];
	}

	int max = sum;
	for (int i = M; i < N; ++i) {
		sum -= prevs[prevIdx];
		std::cin >> prevs[prevIdx];
		sum += prevs[prevIdx];
		++prevIdx; if (prevIdx >= M) { prevIdx = 0; }
		if (max < sum) { max = sum; };
	}

	std::cout << max;

	return 0;
}
