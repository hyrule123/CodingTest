#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
int N, K;
//dp 의미: 배열의 '(index)원'을 가진 동전들로 만들 수 있는 경우의 수
//ex) 3원, 동전 1/2 -> 111, 12 2개
std::vector<int> dp;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> K;
	dp.resize(K + 1);
	dp[0] = true;

	for (int i = 0; i < N; ++i) {
		int coin; std::cin >> coin;
		if (K < coin) { continue; }

		//j - coin에서 가능한 경우의 수를 dp[j]에 더해 준다.
		//ex)dp[3] = 2(111, 12)
		//dp[5] = dp[5](1 <= 11111) + dp[5 - 2] = 2 (111 + 2, 12 + 2)
		//1원을 만들수 있는 경우의 수의 총합에 2원을 추가하는 것이므로
		for (int j = coin; j <= K; ++j) {
			if (dp[j - coin]) { dp[j] += dp[j - coin]; }
		}
	}
	std::cout << dp.back();

	return 0;
}