#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1707 (이분 그래프)
*/
/*
변별 알고리즘(출처: 위키백과)
주어진 그래프가 이분 그래프인지 확인하는 것은 어렵지 않다. 그래프의 꼭짓점들을 깊이 우선 탐색으로 나열한 뒤, 각 꼭짓점들을 이웃 꼭짓점들과 다른 색으로 계속해서 칠해 나가면서, 같은 색깔의 꼭짓점이 서로 연결되어 있는 모순이 발생하는지 여부를 확인하면 된다. 이 알고리즘은 O(|V|+|E|)이다.
*/
//성능비교 해볼것
//1. RED -1 BLUE 1(256ms) /vs/ RED 1, BLUE 2(256ms)
//2. vector<vertex> /vs/ vertex[20000] -> 전자는 clear 하면 vertex.links(이중 vector) 가 날아감, 후자는 수동으로 순회돌면서 초기화
	// -> 6364kb, 256ms /vs/ 11424kb, 232ms
int K, E, V; bool ans;
#include <vector>
#define NOT_VISITED 0
#define RED -1
#define BLUE 1
struct vertex {
	int color = NOT_VISITED;
	std::vector<int> links;
};
vertex vertices[20001];
bool DFS(int vtxIdx, int clr) {
	//색칠 했으면 이번 재귀에서 칠해야하는 색깔과 같은지를 확인
	//만약 다른색일 경우 이분 그래프에서 모순이 되므로 false가 됨
	if (vertices[vtxIdx].color != NOT_VISITED) {
		return vertices[vtxIdx].color == clr;
	}

	vertices[vtxIdx].color = clr;

	//색칠 안했으면 연결된 노드들을 DFS로 호출, 자신의 색깔과 다른 색으로 색칠
	//하나라도 false 나오면 이분그래프가 아니다.
	bool ret = true;
	for (size_t i = 0; i < vertices[vtxIdx].links.size(); ++i) {
		ret = ret && DFS(vertices[vtxIdx].links[i], -clr);
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> K;
	while (K--) {
		std::cin >> V >> E;
		
		for (int i = 1; i < V + 1; ++i) {
			vertices[i].color = NOT_VISITED;
			vertices[i].links.clear();
		}

		for (int i = 1; i <= E; ++i) {
			int a; int b; std::cin >> a >> b;
			vertices[a].links.push_back(b);
			vertices[b].links.push_back(a);
		}

		ans = true;
		for (int i = 1; i <= V; ++i) {
			if (false == vertices[i].links.empty() && NOT_VISITED == vertices[i].color) {
				ans = ans && DFS(i, RED);
			}
		}

		if (ans) {
			std::cout << "YES\n";
		}
		else {
			std::cout << "NO\n";
		}
	}

	return 0;
}