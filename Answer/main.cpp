#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//풀이 참고 - 3번 Kruth Optimization: O(N^2)
//https://js1jj2sk3.tistory.com/3
//https://blog.naver.com/edenooo/221461988510

//점화식이 i~j 구간에서 dp[i][k] + dp[k][j] + C[i][j] 꼴일때 
//num[i][j]란 dp[i][j]가 최소가 되게 하는 k(i  < k  < j)값을 저장하는 배열이라 정의하면, 다음이 성립한다.
//num[i][j - 1] <= num[i][j] <= num[i + 1][j]

//i,j-1  i, j
//		 i+1,j

//현재 C[i][j]부분은 구간합(i번째 파일부터 j번째 파일 용량의 합)
// 단순하게 a=1 <= b=2 <= c=3 <= d=4로 가정하면
//1. 사각부등식 만족
// C[1][3] + C[2][4] <= C[1][4] + C[2][3] -> 1+2+3 + 2+3+4 <= 1+2+3+4 + 2+3 좌변과 우변의 합이 같으므로 성립

//2. 단조증가 만족 일 경우 사용 가능
// 누적합이므로 자명

//지금 문제의 i의 최소값은 1, 최대값은 K 이므로
//1
// 2 
//  3
//   4
//형태의 배열이 된다.

//Knuth 최적화의 요구조건은 다음과 같다(부등호에 =이 없음에 주의)
//min(i  < k  < j) { dp2[i][k] + dp2[k][j] } + psum[i][j]
//그러므로 dp 배열의 의미를 다음과 같이 수정해야 한다
//dp[i][j] == (i + 1, j) 구간 내의 최소값
//현재 dp[i][j] == 기존dp[i-1][j]
using uint = unsigned int;
uint dp[501][501];
uint inputSum[501];

//pivotRanges[i][j]: dp[i][j]가 최소가 되게 하는 pivot
//이 배열도 dp를 구하면서 채워나가야 함
uint pivotRanges[501][501]{};

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	uint T; std::cin >> T;
	for (uint i = 0; i < T; ++i) {
		uint K; std::cin >> K;

		memset(dp, 0, sizeof(uint) * 501 * 501);
		memset(inputSum, 0, sizeof(uint) * 501);
		memset(pivotRanges, 0, sizeof(uint) * 501 * 501);

		for (uint j = 1; j <= K; ++j) {
			uint input; std::cin >> input;
			inputSum[j] = inputSum[j - 1] + input;
			
			//pivotRanges[i][j-1] <= pivotRanges[i][j] <= pivotRanges[i+1][j]
			//
			//dp 루프는 0,2부터 시작 -> 0, 1부터 채워나가야 한다.
			//j는 1부터 시작 -> (0,1)->(1,2)...
			//dp[j-1][j] (==j~j) 를 최소값으로 만들어주는 k = j(pSum[j] - pSum[j] = 0)
			pivotRanges[j - 1][j] = j;
		}

		//[i][j] -> i+1 ~ j
		//[0][1] -> 1~1(=0), [0][2] -> 1~2 (range가 2 이상이여야 최소 1 이상 구간 dp를 확인 가능)
		for (uint range = 2; range <= K; ++range) {
			//대각선 방향으로 dp를 확인
			for (uint r = 0; r + range <= K; ++r) {
				uint c = r + range;
				dp[r][c] = std::numeric_limits<uint>::max();

				for (uint pivot = pivotRanges[r][c - 1]; pivot <= pivotRanges[r + 1][c]; ++pivot) {
					//r+1~pivot + pivot+1~c
					uint prev = dp[r][pivot] + dp[pivot][c];
					if (prev < dp[r][c]) {
						dp[r][c] = prev;
						pivotRanges[r][c] = pivot;
					}
				}

				//r,c == r+1 ~ c 이므로 구간합은 pSum[c] - pSum[r + 1 - 1]
				dp[r][c] += (inputSum[c] - inputSum[r]);
			}
		}

		//r+1 ~ c이므로 1 ~ K 범위가 된다.
		std::cout << dp[0][K] << '\n';
	}

	return 0;
}