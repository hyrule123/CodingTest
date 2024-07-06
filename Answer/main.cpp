#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
struct mat {
	int r{}, c{}, count{};
	//새 행렬의 r,c, 기존 계산횟수에 더해서 이번 계산횟수를 추가
	mat operator *(const mat& _other) {
		return { r , _other.c, count + _other.count + r * c * _other.c };
	}
};
mat dp[501][501];

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	mat prev; std::cin >> prev.r >> prev.c;
	dp[0][0] = prev;
	for (int i = 1; i < N; ++i) {
		mat cur; std::cin >> cur.r >> cur.c;
		dp[i][i] = cur;

		//0~1, 1~2, 3~4...
		dp[i - 1][i] = prev * cur;
		prev = cur;
	}

	//range 1의 경우에는 위 루프에서 미리 계산을 해놨으므로 2부터 시작
	for (int range = 2; range < N; ++range) {
		for (int r = 0; r + range < N; ++r) {
			int c = r + range;
			dp[r][c].count = std::numeric_limits<int>::max();

			for (int pivot = r; pivot < c; ++pivot) {
				//앞쪽의 행렬과 뒤쪽의 행렬을 곱한 결과
				mat result = dp[r][pivot] * dp[pivot + 1][c];

				//연산 횟수가 적을 경우 교체
				if (result.count < dp[r][c].count) {
					dp[r][c] = result;
				}
			}
		}
	}
	std::cout << dp[0][N - 1].count;

	return 0;
}