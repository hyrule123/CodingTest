#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

#include <vector>
#include <algorithm>
int V, E;
struct edge {
	int cost, a, b;
	bool operator<(const edge& _other) {
		return this->cost < _other.cost;
	}
};
std::vector<edge> edges;
std::vector<int> disjoint_set;
std::vector<int> rank;

int find_union(int node) {
	if (disjoint_set[node] != node) {
		disjoint_set[node] = find_union(disjoint_set[node]);
	}
	return disjoint_set[node];
}

void sort(int start, int end) {
	static std::vector<edge> temp(edges.size());
	if (start >= end) { return; }

	const int mid = (start + end) / 2;
	sort(start, mid);
	sort(mid + 1, end);

	int l = start, r = mid + 1, temp_idx = 0;
	while (l <= mid && r <= end) {
		if (edges[l] < edges[r]) {
			temp[temp_idx++] = edges[l++];
		}
		else {
			temp[temp_idx++] = edges[r++];
		}
	}

	for (; l <= mid;) {
		temp[temp_idx++] = edges[l++];
	}
	for (; r <= end; ) {
		temp[temp_idx++] = edges[r++];
	}

	memcpy(edges.data() + start, temp.data(), sizeof(edge) * ((end - start) + 1));
}

int Kruskal_MST() {
	int ret = 0;
	int edge_counts = 0;

	for (int i = 0; i < E; ++i) {
		const edge& e = edges[i];
		int p_a = find_union(e.a);
		int p_b = find_union(e.b);

		//루트 노드가 같으면 사이클이 생성되므로 스킵
		if (p_a == p_b) {
			continue;
		}
			
		//루트 노드 통합
		//rank가 작은 쪽에 붙인다.
		if (rank[p_a] < rank[p_b]) {
			disjoint_set[p_a] = p_b;
		}
		else{
			disjoint_set[p_b] = p_a;
		}

		if(rank[p_a] == rank[p_b])
		{
			++(rank[p_a]);
		}
		
		ret += e.cost;
		++edge_counts;

		//간선의 갯수가 노드 -1개가 되면 스패닝 트리가 완성된 것
		if (V - 1 == edge_counts) {
			break;
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//입력
	std::cin >> V >> E;
	edges.resize(E);

	//disjoint set 초기화
	disjoint_set.resize(V + 1);
	rank.resize(V + 1, 0);
	for (int i = 1; i <= V; ++i) {
		disjoint_set[i] = i;
	}
	//edge 입력 받음
	for (int i = 0; i < E; ++i) {
		std::cin >> edges[i].a >> edges[i].b >> edges[i].cost;
	}

	//edge 정렬
	sort(0, (int)edges.size() - 1);

	//Kruskal MST
	std::cout << Kruskal_MST();

	return 0;
}