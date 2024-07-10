#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//11066 (파일 합치기) - 복습
#include <vector>

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int T; std::cin >> T;
	std::vector<int> f_pSum;	//파일 용량의 구간합
	std::vector<std::vector<int>> dp;	//dp[i][j] i부터 j까지 합쳤을 때의 최소비용
	while (T--) {
		int K; std::cin >> K;
		//file_size_max = 10000, file_count_max = 500 -> 5000000(int로 커버 가능)
		f_pSum.clear(); f_pSum.resize(K + 1);
		for (int i = 1; i <= K; ++i) {
			int input; std::cin >> input;
			f_pSum[i] = f_pSum[i - 1] + input;
		}

		dp.clear();
		dp.resize(K + 1, std::vector<int>(K + 1));

		//[i][i+1] 부터 [i][K]까지 범위를 1씩 늘려가며 탐색한다.
		for (int range = 1; range <= K; ++range) {
			for (int i = 1; i + range <= K; ++i) {
				int j = i + range;

				dp[i][j] = std::numeric_limits<int>::max();

				//pivot을 잡고, 좌/우로 한칸씩 이동하며 각각의 비용 중 최소값을 가져온다.
				for (int pivot = i; pivot < j; ++pivot) {
					dp[i][j] = std::min(dp[i][j], dp[i][pivot] + dp[pivot + 1][j]);
				}

				//이번 파일들을 마지막 하나로 합치는 비용을 추가한다.(이건 언제나 동일함)
				dp[i][j] += f_pSum[j] - f_pSum[i - 1];
			}
		}

		//파일 1번부터 K번까지를 합치는 비용은 dp[1][K]
		std::cout << dp[1][K] << '\n';
	}

	return 0;
}