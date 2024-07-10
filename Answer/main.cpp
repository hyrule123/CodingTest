#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

/*
11066 (파일 합치기) - 복습 2: Knuth Optimization
<사용조건>
1. 어떤 구간을 쪼개는 형태의 점화식
 dp[i][K] + dp[K+1][j] + Cur[i][j]

2. Quadrange Inequalty(사각 부등식) 
 Cur 배열이 Cur[a][c] + Cur[b][d] <= Cur[a][d] + Cur[b][c]
 -> 이 문제에서 Cur[i][j] 는 i~j까지 파일 크기의 누적합이다. Cur[a][c] = A+B+C라고 한다면
 A+B+C + B+C+D <= A+B+C+D + B+C -> 양변이 같으므로 부등식 성립.

3. Monotonicity(단조성)
 Cur[b][c] < Cur[a][d] 
 -> 이 문제에서는 B+C < A+B+C+D -> 항상 성립한다.

계산해야 할 dp인 minIdx가 하나 더 추가됨(dp_knuth[i][j] 의 비용을 최소로 만드는 f_pSum[K]의 K)
i~j범위 사이 K의 범위가 i~j가 아닌 dp_idxRange[i][j-1] <= K <= dp_idxRange[i+1][j] 범위로 줄어듦
 -> 시간복잡도가 O(N^3) -> O(N^2)로 감소

//점화식 dp[i][j] = (i < K < j) min(dp[i][K] + dp[K][j] + f_pSum[i + 1][j])
//i + 1~j 까지의 파일합의 최소비용
*/

#include <vector>

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	struct knuth { int cost, minPivotIdx; };

	int T; std::cin >> T;
	std::vector<int> f_pSum;	//파일 용량의 구간합
	std::vector<std::vector<knuth>> dp_knuth;	//dp[i][j] i부터 j까지 합쳤을 때의 최소비용
	while (T--) {
		int K; std::cin >> K;
		//file_size_max = 10000, file_count_max = 500 -> 5000000(int로 커버 가능)
		f_pSum.clear(); f_pSum.resize(K + 1);
		dp_knuth.clear(); dp_knuth.resize(K + 1, std::vector<knuth>(K + 1));
		for (int i = 1; i <= K; ++i) {
			int input; std::cin >> input;
			f_pSum[i] = f_pSum[i - 1] + input;

			//i - 1 ~ i 범위를 최소로 만드는 인덱스 K는 i 하나뿐이다.
			dp_knuth[i-1][i].minPivotIdx = i;
		}

		//i+1 ~ j 이므로 최소 범위는 2가 되어야 함
		for (int range = 2; range <= K; ++range) {
			//i+1~j 이므로 i는 0부터 시작해야 함
			for (int i = 0; i + range <= K; ++i) {
				int j = i + range;
				dp_knuth[i][j].cost = std::numeric_limits<int>::max();

				for (int pivot = dp_knuth[i][j - 1].minPivotIdx; 
					pivot <= dp_knuth[i + 1][j].minPivotIdx; 
					++pivot) 
				{
					int curCost = dp_knuth[i][pivot].cost + dp_knuth[pivot][j].cost;
					if (curCost < dp_knuth[i][j].cost) {
						dp_knuth[i][j].cost = curCost;
						dp_knuth[i][j].minPivotIdx = pivot;
					}
				}

				//i+1 ~ j 파일의 총합을 더해준다.
				dp_knuth[i][j].cost += f_pSum[j] - f_pSum[i];
			}
		}
		std::cout << dp_knuth[0][K].cost << '\n';
	}
	

	return 0;
}