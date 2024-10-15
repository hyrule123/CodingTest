#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() { 
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <algorithm>
struct set_info {
	int group, rank;
};
struct edge {
	int a, b, cost;
	bool operator < (const edge& e) const {
		return this->cost < e.cost;
	}
};
std::vector<set_info> disjoint_set;
std::vector<edge> edges;

int find_union(int n) {
	if (disjoint_set[n].group != n) {
		disjoint_set[n].group = find_union(disjoint_set[n].group);
	}
	return disjoint_set[n].group;
}
void make_union(int a, int b) {
	if (a == b) { return; }

	if (disjoint_set[a].rank < disjoint_set[b].rank) {
		disjoint_set[a].group = b;
	}
	else {
		disjoint_set[b].group = a;
	}

	if (disjoint_set[a].rank == disjoint_set[b].rank) {
		++(disjoint_set[a].rank);
	}
}

int Kruskal_MST(int node_count) {
	int cost = 0;
	--node_count;
	std::sort(edges.begin(), edges.end());

	for (const edge& e : edges) {
		int pa = find_union(e.a);
		int pb = find_union(e.b);
		if (pa == pb) { continue; }

		cost += e.cost;

		--node_count;
		if (node_count == 0) { break; }

		make_union(pa, pb);
	}

	return cost;
}

void solve()
{
	int m, n;
	while (true) {
		std::cin >> m >> n;
		if (m == 0 && n == 0) { break; }

		edges.clear();
		edges.resize(n);
		disjoint_set.clear();
		disjoint_set.reserve(m);
		for (int i = 0; i < m; ++i) {
			disjoint_set.push_back({ i, 0 });
		}

		int total_cost = 0;
		for (int i = 0; i < n; ++i) {
			std::cin >> edges[i].a >> edges[i].b >> edges[i].cost;
			total_cost += edges[i].cost;
		}

		int min_cost = Kruskal_MST(m);
		std::cout << total_cost - min_cost << '\n';
	}
}
