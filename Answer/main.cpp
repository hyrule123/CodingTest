#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1167 (트리의 지름) : BFS 버전
*/
/*
* 트리의 지름 구하는 법
1. 임의의 노드로부터 제일 먼 곳에 있는 노드 A를 DFS 또는 BFS를 통해 구한다.
2. 노드 A로부터 제일 먼 곳에 있는 노드 B와의 거리가 트리의 지름이 된다.
*/
#include <vector>
#include <bitset>
#include <queue>
struct edge { int to, dist; };
int V;
std::vector<edge> nodes[100001];
std::bitset<100001> visited;
std::queue<edge> q;
edge BFS(int from) {
	visited.reset();
	q.push({ from, 0 });
	visited[from] = true;

	//BFS를 통해 제일 먼 노드 번호와 거리를 구한다.
	edge farthest = { -1, -1 };
	while (false == q.empty()) {
		edge cur = q.front(); q.pop();

		if (farthest.dist < cur.dist) {
			farthest = cur;
		}

		for (const edge& e : nodes[cur.to]) {
			if (visited[e.to]) { continue; }
			visited[e.to] = true;
			q.push({ e.to, cur.dist + e.dist });
		}
	}

	return farthest;
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

	edge farthest_from_1 = BFS(1);

	edge diameter = BFS(farthest_from_1.to);
	std::cout << diameter.dist;

	return 0;
}