#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using int32 = int;

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	int N, K; std::cin >> N >> K;
	std::vector<int> values; values.reserve(N);
	for (int i = 0; i < N; ++i) {
		int val; std::cin >> val;
		if (val == K) {
			std::cout << 1;
			return 0;
		}
		else if (val > K) {
			break;
		}

		values.push_back(val);
	}

	int count = 0;
	for (size_t i = values.size() - 1; i != -1; --i) {
		while (K >= values[i]) {
			K -= values[i];
			++count;
		}
	}
	std::cout << count;

	return 0;
}
