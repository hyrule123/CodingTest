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

int LCSMax = 0;
char a[1002], b[1002];
int dp[1002][1002]{};

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;
	
	std::cin.getline(a + 1, 1001);
	std::cin.getline(b + 1, 1001);
	a[0] = '0', b[0] = '0';	//인덱스 계산에 -1이 필요하므로 완충용으로 하나 넣어줌
	int lenA = (int)std::strlen(a);
	int lenB = (int)std::strlen(b);

	for (int i = 1; i < lenA; ++i) {
		for (int j = 1; j < lenB; ++j) {
			if (a[i] == b[j]) {
				//같은 문자열을 찾았을 경우 -> 둘다 한칸씩 이동
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				//다른 문자열일 경우: i 또는 j에서 한칸씩 이동, 큰 값을 사용한다.
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}

			LCSMax = std::max(LCSMax, dp[i][j]);
		}
	}

	std::cout << LCSMax;
	return 0;
}
