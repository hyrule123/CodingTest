#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 2629 (양팔저울) - 복습
*/
/*
* 추를 올렸을 때 경우의 수: 왼쪽에 올리냐 오른쪽에 올리냐
* 왼쪽에 올리면 전체 무게에서 그만큼 감소, 오른쪽에 올리면 그만큼 증가
* 최소나 최대값을 구하는게 아니므로 안 올리는 선택지는 x
* -> dp[i]->bool: 무게 i를 만들 수 있는가?
*/
#include <vector>
std::vector<int> weights;
std::vector<bool> dp;
int ABS(int i) { if (i < 0) { i = -i; } return i; }

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N, maxWeight = 0; std::cin >> N;
	weights.resize(N + 1);
	for (int i = 0; i < N; ++i) {
		std::cin >> weights[i];
		maxWeight += weights[i];
	}
	dp.resize(maxWeight + 1);

	dp[0] = true; dp[weights[0]] = true;
	for (int i = 1; i < N; ++i) {
		//연쇄효과 방지를 위해 역순으로(ex.2 -> 순차적으로 할시 2, 4, 6, 8, ... true로 만들어버리므로)
		for (int w = maxWeight - weights[i]; w >= 0; --w) {
			if (dp[w]) { dp[w + weights[i]] = true; }
		}

		//마찬가지로 연쇄효과 방지를 위해 순차적으로, 음수 방지를 위해 절대값
		for (int w = 0; w <= maxWeight; ++w) {
			if (dp[w]) { dp[ABS(w - weights[i])] = true; }
		}
	}

	int nOrb; std::cin >> nOrb;
	while (nOrb--) {
		int orb; std::cin >> orb;
		char result = 'N';
		//이 구슬이 범위 안에 있고 구슬의 무게를 저울로 표현할수 있으면
		if (orb <= maxWeight && dp[orb]) {
			result = 'Y';
		}
		std::cout << result << ' ';
	}

	return 0;
}