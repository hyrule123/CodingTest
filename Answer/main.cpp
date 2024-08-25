#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1167 (트리의 지름) : DFS 버전
*/
/*
* 트리의 지름 구하는 법
1. 임의의 노드로부터 제일 먼 곳에 있는 노드 A를 DFS를 통해 구한다.
2. 노드 A로부터 제일 먼 곳에 있는 노드 B와의 거리가 트리의 지름이 된다.
*/
#include <vector>
#include <bitset>
struct edge { int to, dist; };
int V;
std::vector<edge> nodes[100001];
std::bitset<100001> visited;
int farthest_node = -1, max_dist = -1;
void DFS(int node, int acc_dist) {
	visited[node] = true;

	if (max_dist < acc_dist) {
		max_dist = acc_dist;
		farthest_node = node;
	}

	for (const edge& e : nodes[node]) {
		if (visited[e.to]) { continue; }
		DFS(e.to, acc_dist + e.dist);
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> V;
	for (int i = 1; i <= V; ++i) {
		int node, to, dist; std::cin >> node;

		while (true) {
			std::cin >> to;
			if (to == -1) { break; }
			std::cin >> dist;

			nodes[node].push_back({ to, dist });
		}
	}

	//1번 노드로부터 제일 먼 노드 A를 구한다.
	DFS(1, 0);
	int farthest_from_1 = farthest_node;
	farthest_node = -1;
	max_dist = -1;
	visited.reset();

	//A로부터 제일 먼 노드를 구하고, 그 거리를 출력하면 그게 트리의 지름이 된다.
	DFS(farthest_from_1, 0);
	std::cout << max_dist;

	return 0;
}