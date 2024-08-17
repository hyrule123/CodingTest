#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 14002 (가장 긴 증가하는 부분 수열 4) : 갯수가 1000개 이므로 O(N^2) 방식으로 가능
*/
#include <stack>
int N, arr[1001], dp[1001];

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> arr[i];
		dp[i] = 1;
	}

	int longest = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[j] < arr[i]) {
				dp[i] = std::max(dp[i], dp[j] + 1);
				longest = std::max(longest, dp[i]);
			}
		}
	}

	std::cout << longest << '\n';
	std::stack<int> log;
	for (int i = N - 1; i >= 0; --i) {
		if (dp[i] == longest) {
			--longest;
			log.push(arr[i]);
		}
		if (longest == 0) {
			break;
		}
	}
	while (false == log.empty()) {
		std::cout << log.top() << ' ';
		log.pop();
	}

	return 0;
}