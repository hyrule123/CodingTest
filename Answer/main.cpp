#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//이번 앱을 끄거나 켜거나
#include <vector>
struct app { int mem, cost; };
std::vector<app> apps;
//i = i번째 앱까지 , j: 제거 비용, val: 제거되는 최대 메모리
std::vector<std::vector<int>> dp;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N, M; std::cin >> N >> M;
	apps.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		std::cin >> apps[i].mem;
	}
	int maxCost = 0;
	for (int i = 1; i <= N ; ++i) {
		std::cin >> apps[i].cost;
		maxCost += apps[i].cost;
	}

	int minCost = std::numeric_limits<int>::max();
	//최악의 경우 최대 비용은 100 * 100 = 10000
	dp.resize(N + 1, std::vector<int>(maxCost + 1));
	for (int i = 1; i <= N; ++i) {

		for (int j = 0; j <= maxCost; ++j) {
			//이번 앱을 제거하지 않았을 때
			int exclude = dp[i - 1][j];

			//이번 앱을 제거했을 때: [j - (이번앱 cost)].mem + (이번앱 mem)
			int include = 0;
			if (apps[i].cost <= j) {
				include = dp[i - 1][j - apps[i].cost] + apps[i].mem;
			}

			dp[i][j] = std::max(exclude, include);
			if (M <= dp[i][j]) {
				minCost = std::min(minCost, j);
			}
		}
	}
	std::cout << minCost;


	return 0;
}