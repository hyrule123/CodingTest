#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 7579 (앱) - 복습 + 메모리 사용량 다이어트 버전(6096kb -> 2220kb)
*/
#include <vector>
struct app { int mem, cost; };
//나올수 있는 최대 값: 100 * 1000만 = 1'000'000'000 10억
//앱 한 개당 경우의 수: 이 앱을 제거하거나 제거하지 않거나
//dp[i][j]: 앱을 i개까지 검사했을 때, 비용 j로 제거할 수 있는 메모리의 최대 용량
std::vector<app> apps;

#include <array>
//0, 1 toggle 해가면서 prev와 cur 바꿀 예정
std::vector<std::array<int, 2>> dp;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N, M, maxCost = 0; std::cin >> N >> M;
	apps.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		std::cin >> apps[i].mem;
	}
	for (int i = 1; i <= N; ++i) {
		std::cin >> apps[i].cost;
		maxCost += apps[i].cost;
	}

	dp.resize(maxCost + 1);
	bool prev = false;
	int minCost = std::numeric_limits<int>::max();
	for (int i = 1; i <= N; ++i) {
		bool cur = !prev;

		//비용 0인 앱도 있으므로 0부터 해야함(주의 - 복습중에 틀렸음)
		for (int c = 0; c <= maxCost; ++c) {
			//안 지우면 지난 앱검사때 들었던 비용 그대로이므로 가져옴
			int notDelete = dp[c][prev];
			
			int Delete = 0;
			//현재 비용(c)에서 i번째 앱을 지울 수 있을 경우 제거
			if (c >= apps[i].cost) {
				Delete = dp[c - apps[i].cost][prev] + apps[i].mem;
			}
			dp[c][cur] = std::max(notDelete, Delete);

			//최소 삭제 메모리 조건 충족 + 필요 코스트가 최소 코스트보다 낮을 경우 갱신
			if (M <= dp[c][cur] && c < minCost) { minCost = c; }
		}

		prev = !prev;
	}
	std::cout << minCost;

	return 0;
}