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
	std::vector<int> arr(N + 1);

	std::cin >> arr[1];
	for (int i = 2; i <= N; ++i) {
		std::cin >> arr[i];
		arr[i] += arr[i - 1];
	}

	for (int i = 1; i <= M; ++i) {
		int a, b; std::cin >> a >> b;
		std::cout << arr[b] - arr[a - 1] << '\n';
	}

	return 0;
}
