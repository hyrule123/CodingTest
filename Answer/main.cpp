#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();
int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
using ll = long long;
struct edge {
	double dist;
	int a, b;
	auto operator < (const edge& other) const {
		return this->dist < other.dist;
	}
};
struct set_info { int root, rank; };
struct node {
	ll x, y;
	double dist(const node& other) {
		ll xx = this->x - other.x;
		ll yy = this->y - other.y;
		return std::sqrt(xx * xx + yy * yy);
	}
};

int N, M;
std::vector<node> nodes;
std::vector<set_info> disjoint_set;
std::vector<edge> edges;

int find_union(int n) {
	if (disjoint_set[n].root != n) {
		disjoint_set[n].root = find_union(disjoint_set[n].root);
	}
	return disjoint_set[n].root;
}

void make_union(int a, int b) {
	if (a == b) { return; }

	//height가 높은 쪽에 붙여준다.
	if (disjoint_set[a].rank < disjoint_set[b].rank) {
		disjoint_set[a].root = b;
	}
	else {
		disjoint_set[b].root = a;
	}

	//같다면, root 노드가 가서 붙은 쪽의 height를 1 늘려준다.
	//이 코드에서는 같을 때 b가 a에 가서 붙었으므로 a를 늘려주면 된다.
	if (disjoint_set[a].rank == disjoint_set[b].rank) {
		++(disjoint_set[a].rank);
	}
}


void solve()
{
	std::cin >> N >> M;
	nodes.resize(N + 1);
	disjoint_set.resize(N + 1);
	edges.reserve(N * N);
	
	int remaining_edges = N - 1;
	
	for (int i = 1; i <= N; ++i) {
		std::cin >> nodes[i].x >> nodes[i].y;
		disjoint_set[i].root = i;
		disjoint_set[i].rank = 0;
	}

	for (int i = 1; i <= M; ++i) {
		int a, b; std::cin >> a >> b;
		a = find_union(a);
		b = find_union(b);

		if (a == b) {
			continue;
		}

		//union이 일어 났으면 사이클 없는 간선이 연결되었다는 뜻
		//이러면 찾아야 할 edge 수가 하나 적어진다.
		--remaining_edges;
		make_union(a, b);
	}

	for (int i = 1; i <= N; ++i) {
		int group_i = find_union(i);

		for (int j = i + 1; j <= N; ++j) {
			int group_j = find_union(j);

			if (group_i == group_j) {
				continue;
			}
			
			//같은 그룹에 속하지 않은 노드 사이의 거리를 구해서 배열에 넣어준다.
			edges.push_back({ nodes[i].dist(nodes[j]), i, j });
		}
	}
	
	//정렬 하고
	std::sort(edges.begin(), edges.end());

	double total = 0.f;
	for (const edge& e : edges) {
		int g_a = find_union(e.a);
		int g_b = find_union(e.b);

		if (g_a == g_b) { continue; }

		total += e.dist;

		//모든 edge를 다 찾았으면 중단
		if (--remaining_edges == 0) {
			break;
		}

		make_union(g_a, g_b);
	}

	printf("%.2lf", total);
}
