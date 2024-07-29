#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11657 (타임머신)
*/
using int64 = long long;
constexpr int64 INF = std::numeric_limits<int64>::max();
struct edge { int from, to; int64 dist; };
#include <vector>
std::vector<edge> edges;
int N, M;
int64 dp[501];

bool BellmanFord() {
	dp[1] = 0;

	//N - 1번 만큼 모든 간선을 순회돌아준다.
	for (int64 from = 1; from <= N - 1; ++from) {
		for (const edge& e : edges) {
			if (dp[e.from] == INF) { continue; }

			//이번 간선을 타고 온게 지난번 간선을 타고 온것보다 짧을 경우 갱신
			dp[e.to] = std::min(dp[e.to], dp[e.from] + e.dist);
		}
	}

	//마지막 N번째 반복: 음수 사이클 확인
	for (const edge& e : edges) {
		if (dp[e.from] == INF) { continue; }

		//여전히 짧아질 수 있는 거리가 존재할 경우 음수 사이클이 있는것
		if (dp[e.from] + e.dist < dp[e.to]) {
			return false;
		}
	}

	return true;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	//초기화 및 input
	for (int i = 0; i < 501; ++i) {
		dp[i] = INF;
	}
	std::cin >> N >> M;
	edges.reserve(M);
	for (int i = 0; i < M; ++i) {
		int A, B; int64 C; std::cin >> A >> B >> C;
		edges.push_back({ A, B, C });

	}

	//벨만포드 알고리즘 시행
	//음수 사이클 있는 경우 -1 출력 후 return
	if (false == BellmanFord()) {
		std::cout << -1;
		return 0;
	}

	//2번 노드부터 순서대로 출력
	for (int i = 2; i <= N; ++i) {
		std::cout << (dp[i] == INF ? -1ll : dp[i]) << '\n';
	}

	return 0;
}