#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

#include <vector>
#include <bitset>

int T, N, M;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> T;
	while (T--) {
		std::cin >> N >> M;

		//정담: Spanning Tree가 되기 위한 edge 수는 node 수 - 1
		std::cout << N - 1 << '\n';

		for (int i = 0; i < M; ++i) {
			int dummy_a, dummy_b; std::cin >> dummy_a >> dummy_b;
		}
	}

	return 0;
}