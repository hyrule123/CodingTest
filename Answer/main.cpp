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
#include <cmath>
#include <stack>
using ll = long long;
constexpr ll MAX = 100'001;
struct Edge { int dest, dist; };
struct Node { int parent; ll dist; };
using Tree = vector<vector<Node>>;

void build_tree(const vector<vector<Edge>>& graph, Tree& tree, vector<int>& depth) {
	const size_t log_max = (size_t)ceil(log2(graph.size())) + 1;
	tree.resize(graph.size(), vector<Node>(log_max));
	depth.resize(graph.size());

	stack<int> stk;
	vector<bool> visited(graph.size());
	visited[1] = true;
	stk.push(1);
	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();

		for (const auto& next : graph[cur]) {
			if (visited[next.dest]) { continue; }
			visited[next.dest] = true;
			
			tree[next.dest][0].parent = cur;
			tree[next.dest][0].dist = next.dist;
			depth[next.dest] = depth[cur] + 1;
			stk.push(next.dest);
		}
	}
}

void pre_compute(Tree& tree) {
	for (size_t i = 1; i < tree[0].size(); ++i) {
		for (size_t j = 1; j < tree.size(); ++j) {
			auto& cur = tree[j][i];
			const auto&
				fx = tree[j][i - 1],
				//tree[tree[j][i-1]][i-1]
				fxx = tree[fx.parent][i - 1];

			cur.dist = fx.dist + fxx.dist;
			cur.parent = fxx.parent;
		}
	}
}

ll query_1(const Tree& tree, const vector<int>& depth, int a, int b) {
	if (depth[a] < depth[b]) {
		swap(a, b);
	}

	ll dist = 0;
	int depth_diff = depth[a] - depth[b];
	for (int shift = 0; shift < (int)tree[0].size(); ++shift) {
		int bit = 1 << shift;
		if (depth_diff < bit) { break; }
		if (depth_diff & bit) {
			dist += tree[a][shift].dist;
			a = tree[a][shift].parent;
		}
	}

	if (a != b) { 
		for (int shift = (int)tree[0].size() - 1; shift >= 0; --shift) {
			if (tree[a][shift].parent == tree[b][shift].parent) { continue; }

			dist += tree[a][shift].dist + tree[b][shift].dist;
			a = tree[a][shift].parent;
			b = tree[b][shift].parent;
		}
		dist += tree[a][0].dist + tree[b][0].dist;
	}

	return dist;
}
int query_2(const Tree& tree, const vector<int>& depth, int from, int to, int k) {
	//k: k번째 노드 -> from에서 k-1 간선 개수만큼 이동하는걸로 변경
	--k;

	//간선 0개면 from 반환
	if (k == 0) {
		return from;
	}
	
	int a = from, b = to;
	if (depth[a] < depth[b]) {
		swap(a, b);
	}

	int depth_diff = depth[a] - depth[b];
	for (int shift = 0; shift < (int)tree[0].size(); ++shift) {
		int bit = 1 << shift;
		if (depth_diff < bit) { break; }
		if (depth_diff & bit) {
			a = tree[a][shift].parent;
		}
	}

	if (a != b) {
		for (int shift = (int)tree[0].size() - 1; shift >= 0; --shift) {
			if (tree[a][shift].parent == tree[b][shift].parent) { continue; }
			a = tree[a][shift].parent;
			b = tree[b][shift].parent;
		}

		a = tree[a][0].parent;
		b = tree[b][0].parent;
	}

	//전체 간선 개수
	int total_len = depth[from] + depth[to] - 2 * depth[a];
	if (k == total_len) { return to; }

	//LCA와 from 사이 간선 개수를 구한다
	int from2LCA = depth[from] - depth[a], 
		ret = from;
	
	if (from2LCA < k) {
		k = total_len - k;
		ret = to;
	}

	//from 혹은 to로부터 k 혹은 k - from2LCA 거리의 노드를 반환
	for (int shift = 0; shift < tree[0].size(); ++shift) {
		int bit = 1 << shift;
		if (k < bit) { break; }
		if (bit & k) {
			ret = tree[ret][shift].parent;
		}
	}
	return ret;
}

void solve() {
	ll N; cin >> N;
	vector<vector<Edge>> graph;
	graph.resize(N + 1);
	for (int i = 1; i <= N - 1; ++i) {
		int u, v, w; cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	
	vector<int> depth;
	Tree tree;

	build_tree(graph, tree, depth);
	pre_compute(tree);

	int M; cin >> M;
	while (M--) {
		int q; cin >> q;
		if (q == 1) {
			int a, b; cin >> a >> b;
			cout << query_1(tree, depth, a, b) << '\n';
		}
		else if(q == 2) {
			int a, b, c; cin >> a >> b >> c;
			cout << query_2(tree, depth, a, b, c) << '\n';
		}
	}
}