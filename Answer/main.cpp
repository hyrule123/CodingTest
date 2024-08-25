#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11780 (플로이드 2)
*/
/*
플로이드 개념: dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
//저장된 i~j 거리와 k를 경유해서 오는 거리를 비교
*/
#include <vector>
constexpr int INF = (int)1e6;
struct edge {
	int dist = INF;
};

int n_nodes, n_edges;
edge memo[101][101];

void floyd() {
	for (int stop_over = 1; stop_over <= n_nodes; ++stop_over) {
		for (int from = 1; from <= n_nodes; ++from) {
			for (int to = 1; to <= n_nodes; ++to) {
				memo[from][to].dist = std::min(memo[from][to].dist, memo[from][stop_over].dist + memo[stop_over][to].dist);
			}
		}
	}

	for (int i = 1; i <= n_nodes; ++i) {
		for (int j = 1; j <= n_nodes; ++j) {
			int output = memo[i][j].dist == INF ? 0 : memo[i][j].dist;
			std::cout << output << ' ';
		}
		std::cout << '\n';
	}
}

void trace_back() {

}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	std::cin >> n_nodes >> n_edges;
	for (int i = 1; i <= n_nodes; ++i) {
		memo[i][i].dist = 0;
	}
	for (int i = 0; i < n_edges; ++i) {
		int from, to, cost; std::cin >> from >> to >> cost;
		memo[from][to].dist = cost;
	}

	floyd();
	trace_back();

	return 0;
}