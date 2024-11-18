#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <array>
#include <vector>
#include <stack>

struct node {
	int parent;
	vector<int> childs;
};
constexpr int MAX = (int)1e5 + 1;
int N, R, Q;
array<node, MAX> graph;
array<int, MAX> dp;

void build_parent(int cur, int par) {
	graph[cur].parent = par;

	for (int next : graph[cur].childs) {
		if (next == par) { continue; }
		build_parent(next, cur);
	}
}

int query(int u) {
	if (dp[u] == 0) {
		dp[u] = 1;

		for (int next : graph[u].childs) {
			if (next == graph[u].parent) { continue; }
			dp[u] += query(next);
		}
	}
	return dp[u];
}

void solve() {
	cin >> N >> R >> Q;
	for (int i = 1; i <= N - 1; ++i) {
		int u, v; cin >> u >> v;
		graph[u].childs.push_back(v);
		graph[v].childs.push_back(u);
	}

	build_parent(R, 0);

	for (int i = 1; i <= Q; ++i) {
		int u; cin >> u;
		cout << query(u) << '\n';
	}
}