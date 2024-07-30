#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1956 (운동)
*/
//플로이드-워셜 알고리즘 사용
//-> 모든 그래프에 대해 최단거리를 구할 수 있음, O(N^3)
//하나의 사이클에서 나올 수 있는 최대 거리는 10000 * 400 * 399 = 15억 9천 6백만(uint 범위 이내)
using uint = unsigned int;
constexpr uint INF = (uint)2e9;
uint V, E;
struct Node {
	uint dist = INF;
};
Node edges[401][401];

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	//Input
	std::cin >> V >> E;
	for (uint i = 0; i < E; ++i) {
		uint a, b, c; std::cin >> a >> b >> c;
		edges[a][b].dist = c;
	}

	//Floyd-Warshall
	for (uint turnPoint = 1; turnPoint <= V; ++turnPoint) {
		for (uint from = 1; from <= V; ++from) {
			for (uint to = 1; to <= V; ++to) {
				edges[from][to].dist = std::min(edges[from][to].dist, edges[from][turnPoint].dist + edges[turnPoint][to].dist);
			}
		}
	}

	//[i][i]에 다른 곳으로 갔다가 자신에게 돌아오는 최단경로가 저장되었을 것이다.
	uint shortest = INF;
	for (uint i = 1; i <= V; ++i) {
		shortest = std::min(shortest, edges[i][i].dist);
	}
	if (shortest == INF) { std::cout << -1; }
	else { std::cout << shortest; }

	return 0;
}