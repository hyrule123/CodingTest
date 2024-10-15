#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <array>
//참고: 벨만-포드 알고리즘은 기록을 누적시키고 누적된 기록끼리 합산시키므로 값이 매우 커질 수 있음에 주의
using ll = long long;
constexpr ll INF = std::numeric_limits<ll>::max();
ll dp[501];//1~500
struct edge {
	ll dest, dist;
};
ll N, M;
std::array<std::vector<edge>, 501> graph;


void solve() {
	std::cin >> N >> M;
	for (ll i = 1; i <= N; ++i) {
		dp[i] = INF;
	}
	for (ll i = 1; i <= M; ++i) {
		ll a, b, c; std::cin >> a >> b >> c;
		graph[a].push_back({ b, c });
	}

	dp[1] = 0;
	//노드 수 - 1회 만큼 반복
	for (ll t = 1; t <= N - 1; ++t) {

		//Edge 순회
		for (ll i = 1; i <= N; ++i) {
			const auto& edges = graph[i];
			for (const auto& e : edges) {
				if (dp[i] == INF) { continue; }

				//i 노드에서 dest 노드로 가는게 기존 방법보다 더 빠르게 갈수 있을 경우 갱신
				if (dp[e.dest] > dp[i] + e.dist) {
					dp[e.dest] = dp[i] + e.dist;
				}
			}
		}
	}

	//마지막 체크 순회
	for (ll i = 1; i <= N; ++i) {
		const auto& edges = graph[i];
		for (const auto& e : edges) {
			if (dp[i] == INF) { continue; }

			//아직도 경로가 감소 중이면(무한 감소 사이클이 있으면)
			//-1 출력하고 바로 리턴
			if (dp[e.dest] > dp[i] + e.dist) {
				std::cout << -1; return;
			}
		}
	}

	//2번 도시부터 가는데 얼마나 걸리는지 출력
	for (ll i = 2; i <= N; ++i) {
		std::cout << (dp[i] == INF ? -1 : dp[i]) << '\n';
	}
}