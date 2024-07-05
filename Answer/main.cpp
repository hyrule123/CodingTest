#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//풀이 참고 - 1번 정석 DP 풀이 : O(N^3)
//https://js1jj2sk3.tistory.com/3

//dp[i][j] == i번 파일부터 j번 파일(i < j)을 합치는데 드는 최소비용
//ex)3, 4, 5는 3/45와 34/5 두가지 경우의 수로 나눌 수 있다
//또한 더했을 때만 비용에 합산한다. 아래 예시에서 괄호친 부분만 더하면 됨
//3 / 45 -> 3 / (9) -> (12) = 9 + 12 = 21
//== dp[3][3] + dp[4][5] + {3부터 5까지의 구간합}
//0 + 9 + 12 = 21
//cf)dp[3][3] == 0 (i < j)

//34 / 5 -> (7) / 5 -> (12) = 7 + 12 = 19
//뭘 하던 마지막에 12(==3 + 4 + 5)를 더하는 것은 같음 -> i~j까지의 구간합
int dp[501][501]{};

//누적합(최대 10000 * 500 = 5000000)
int inputSum[501]{};

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int T; std::cin >> T;
	for (int i = 0; i < T; ++i) {
		int K; std::cin >> K;
		for (int j = 1; j <= K; ++j) {
			int input; std::cin >> input;
			inputSum[j] = inputSum[j - 1] + input;
		}

		//for문이 이렇게 생겨먹은 이유
		//dp[1][2] = 1부터 2까지의 최소합
		//dp[1][5] = 1부터 5까지의 최소합
		//1~5 안에는 1~1부터 1~5까지 모두 포함되어 있다.
		//하위 범주를 먼저 계산해야 정상적인 DP 계산이 가능하다는 것
		//그러므로 1~1, 1~2, 1~3, 1~4... 5~5 모두 계산이 되어 있어야 한다.->작은 범위부터 채워나간다
		for (int range = 1; range <= K; ++range) {
			for (int r = 1; r + range <= K; ++r) {
				int c = r + range;
				dp[r][c] = std::numeric_limits<int>::max();

				for (int pivot = r; pivot < c; ++pivot) {
					dp[r][c] = std::min(dp[r][c],
						dp[r][pivot] + dp[pivot + 1][c]
					);
				}
				dp[r][c] += inputSum[c] - inputSum[r - 1];
			}
		}
		
		//1~K(전체 구간)의 합은 dp[1][K]에 저장되었을 것이다.
		std::cout << dp[1][K]<<'\n';
	}

	return 0;
}