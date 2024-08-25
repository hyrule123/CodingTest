#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11725 (트리의 부모 찾기)
*/
#include <vector>
#include <queue>
std::vector<int> tree[100001];
int N, ans[100001];

void BFS() {
	std::queue<int> q;

	//루트인 1부터 넣어준다. 1에 가까운 노드 = 트리 기준 1의 자식 노드들
	q.push(1);
	ans[1] = 0;

	while (false == q.empty()) {
		int idx = q.front(); q.pop();

		for (int child : tree[idx]) {
			if (ans[child] == -1) {
				ans[child] = idx;
				q.push(child);
			}
		}
	}

	for (int i = 2; i <= N; ++i) {
		std::cout << ans[i] << '\n';
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	memset(ans, -1, sizeof(ans));
	
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		int a, b; std::cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	BFS();

	return 0;
}