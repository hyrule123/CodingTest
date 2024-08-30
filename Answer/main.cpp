#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 20040 (사이클 게임)
*/
/* 
* GPT한테 물어보니 무방향 그래프에만 적용 가능하다고 함
* 유방향 그래프는 DFS를 통해서 판별해야 함
*/
#include <bitset>
constexpr int MAX = 500'000;
int n, m, graph[MAX];
std::bitset<MAX> visited;

int find_group(int i) {
	if (graph[i] != i) {
		graph[i] = find_group(graph[i]);
	}

	return graph[i];
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		graph[i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		int a, b; std::cin >> a >> b;

		int group_a = find_group(a);
		int group_b = find_group(b);

		//합치기 전에 이미 같은 그룹에 속해 있다면 어딘가 회로가 있다는 뜻
		//i를 출력하고 return
		if (group_a == group_b) {
			std::cout << i;
			return 0;
		}

		if (group_a < group_b) {
			graph[group_a] = group_b;
		}
		else {
			graph[group_b] = group_a;
		}
	}

	//회로를 발견하지 못했다면 이 코드가 실행됨.
	std::cout << 0;

	return 0;
}