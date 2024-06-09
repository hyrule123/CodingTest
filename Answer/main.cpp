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
	
	int N, K; std::cin >> N >> K;
	//row(i): 가방에 넣은 물건 수, col(j): 현재 무게에서 가질수 있는 최대 가치
	std::vector<std::vector<int>> dp(N + 1, std::vector<int>(K + 1));

	for (int i = 1; i <= N; ++i) {
		int weight, value; std::cin >> weight >> value;

		for (int j = 1; j <= K; ++j) {
			//이번 짐 안 넣었을 때: 이전 값(i-1개 짐을 넣었을 때 그대로 사용)
			int except = dp[i - 1][j];

			//이번짐 넣었을 때: 이전 값 중 이번에 넣을 짐의 무게를 뺀 곳의 값 + value
			int include{};
			if (j >= weight) {
				include = dp[i - 1][j - weight] + value;
			}
			dp[i][j] = std::max(except, include);
		}
	}
	std::cout << dp[N][K];

	return 0;
}
