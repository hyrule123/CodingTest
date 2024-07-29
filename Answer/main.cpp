#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11404 (플로이드)
*/
/*
* 플로이드 워셜 알고리즘
* 점화식: D(ab) = min{ D(ab), D(ak) + D(kb) }
* -> a -> b 직통 vs a -> k -> b 경유
*/
int costs[101][101], n, m;
constexpr int INF = (int)1e9;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//Input
	for (int i = 1; i <= 100; ++i) {
		for (int j = 1; j <= 100; ++j) {
			//자신->자신으로는 갈수 없음
			if (i == j) { costs[i][j] = 0; }
			else { costs[i][j] = INF; }
		}
	}

	std::cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, c; std::cin >> a >> b >> c;
		//노선이 여러개일수도 있다.
		costs[a][b] = std::min(costs[a][b], c);
	}

	//Solve
	for (int stopover = 1; stopover <= n; ++stopover) {
		for (int from = 1; from <= n; ++from) {
			for (int to = 1; to <= n; ++to) {
				costs[from][to]
					= std::min(costs[from][to], costs[from][stopover] + costs[stopover][to]);
			}
		}
	}

	//Output
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int output = costs[i][j] == INF ? 0 : costs[i][j];
			std::cout << output << ' ';
		}

		std::cout << '\n';
	}

	return 0;
}