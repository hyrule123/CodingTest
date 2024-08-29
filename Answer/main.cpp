#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1976 (여행 가자)
*/
#include <bitset>
constexpr int MAX = 201;
int n_node, n_stopover, graph[MAX];

int find_group(int node) {
	if (graph[node] != node) {
		graph[node] = find_group(graph[node]);
	}
	
	return graph[node];
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n_node >> n_stopover;
	for (int i = 1; i <= n_node; ++i) {
		graph[i] = i;
	}

	
	for (int i = 1; i <= n_node; ++i) {
		for (int j = 1; j <= n_node; ++j) {
			int is_linked; std::cin >> is_linked;

			//두 노드가 연결되어 있으면 하나의 집합으로 묶는다
			if (is_linked) {
				int group_i = find_group(i);
				int group_j = find_group(j);

				if (group_i < group_j) {
					graph[group_i] = group_j;
				}
				else {
					graph[group_j] = group_i;
				}
			}
		}
	}

	//지정된 경유지를 모두 방문할 수 있는지 확인한다.
	bool travel_possible = true;

	//첫 번째 경유지의 그룹을 확인
	int group_num; std::cin >> group_num;
	group_num = find_group(group_num);

	for (int i = 2; i <= n_stopover; ++i) {
		int stopover; std::cin >> stopover;
		
		//전부 동일한 그룹에 속해있는지를 확인한다. 하나라도 그룹이 다를경우 경유 불가능하다는 뜻 
		travel_possible = travel_possible && (group_num == find_group(stopover));
	}
	if (travel_possible) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}

	return 0;
}