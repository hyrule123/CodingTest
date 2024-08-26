#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1967 (트리의 지름)
*/
//동일 문제: 백준 1167
//BFS, DFS 둘 다 가능하지만 공간복잡도를 생각했을 때 DFS가 좀 더 유리한듯
#include <vector>
#include <bitset>
struct edge { int to, dist; };
int n_node, farthest_node = -1, farthest_dist = -1;
std::vector<edge> childs[10001];
std::bitset<10001> visited;
void DFS(int cur, int acc_dist) {
	visited[cur] = true;

	if (farthest_dist < acc_dist) {
		farthest_node = cur;
		farthest_dist = acc_dist;
	}

	for (const edge& e : childs[cur]) {
		if (false == visited[e.to]) {
			DFS(e.to, acc_dist + e.dist);
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n_node;
	for (int i = 0; i < n_node - 1; ++i) {
		int a, b, dist; std::cin >> a >> b >> dist;
		childs[a].push_back({ b, dist });
		childs[b].push_back({ a, dist });
	}

	DFS(1, 0);

	int farthest_from_1 = farthest_node;
	farthest_node = -1;
	farthest_dist = -1;
	visited.reset();
	DFS(farthest_from_1, 0);

	std::cout << farthest_dist;

	return 0;
}