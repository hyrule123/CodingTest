#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 2293 (동전 1) - 복습
*/
#include <vector>
std::vector<int> dp;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int n, k; std::cin >> n >> k;

	dp.resize(k + 1);
	dp[0] = 1;
	while (n--) {
		int coin; std::cin >> coin;

		//i원을 만들 수 있을 경우 i + coin 원도 만들수 있게 된다.
		for (int i = 0; i + coin <= k; ++i) {
			if (dp[i]) { dp[i + coin] += dp[i]; }
		}
	}
	std::cout << dp.back();

	return 0;
}