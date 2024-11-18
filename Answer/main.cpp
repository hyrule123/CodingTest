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

//백준 3176 (도로 네트워크) [LCA: 이전 풀이보다 효율적(292ms -> 160ms)]
//경로를 찾는다는건 곧 최소 공통 조상을 찾은 뒤 그 조상을 거쳐 이동하는 것이므로
//LCA 알고리즘으로 찾을 수 있을 듯
#include <vector>
#include <stack>
using l = long;
using ll = long long;

struct edge { l dest, dist; };
struct dp { l par, min, max; };

constexpr l MAX = 100'001, LOG_MAX = 18;
vector<edge> edges[MAX];
l N, depth[MAX];
dp parent_of[LOG_MAX][MAX];

void build_tree() {
	vector<bool> visited; visited.resize(N + 1);
	stack<l> stk;
	stk.push(1);
	visited[1] = true;
	parent_of[0][1].max = -1;
	parent_of[0][1].min = 1'000'001;

	while (false == stk.empty()) {
		l cur = stk.top(); stk.pop();

		for (const edge& next : edges[cur]) {
			if (visited[next.dest]) { continue; }
			visited[next.dest] = true;

			parent_of[0][next.dest].par = cur;
			parent_of[0][next.dest].max = next.dist;
			parent_of[0][next.dest].min = next.dist;
			depth[next.dest] = depth[cur] + 1;

			stk.push(next.dest);
		}
	}
}

void query(l a, l b) {
	l _max = -1, _min = 1'000'001;

	if (depth[a] > depth[b]) {
		swap(a, b);
	}

	l depth_diff = depth[b] - depth[a];
	for (l shift = 0; shift < LOG_MAX; ++shift) {
		l bit = 1 << shift;
		if (bit > depth_diff) { break; }
		if (depth_diff & bit) {
			_min = min(_min, parent_of[shift][b].min);
			_max = max(_max, parent_of[shift][b].max);
			b = parent_of[shift][b].par;
		}
	}

	//LCA를 발견하지 못했다면
	if (a != b) {
		//LCA의 자식 노드를 탐색
		for (l shift = LOG_MAX - 1; shift >= 0; --shift) {
			if (parent_of[shift][a].par == parent_of[shift][b].par) { continue; }

			_min = min(_min, min(parent_of[shift][a].min, parent_of[shift][b].min));
			_max = max(_max, max(parent_of[shift][a].max, parent_of[shift][b].max));
			a = parent_of[shift][a].par;
			b = parent_of[shift][b].par;
		}

		//LCA 바로 밑 노드 -> LCA
		_min = min(_min, min(parent_of[0][a].min, parent_of[0][b].min));
		_max = max(_max, max(parent_of[0][a].max, parent_of[0][b].max));
	}

	cout << _min << ' ' << _max << '\n';
}

void solve() {
	cin >> N;
	for (l i = 1; i <= N - 1; ++i) {
		l a, b, c; cin >> a >> b >> c;
		edges[a].push_back({ b, c });
		edges[b].push_back({ a, c });
	}

	//1번을 루트노드로 트리를 구성
	build_tree();

	//dp precompute
	for (l i = 1; i < LOG_MAX; ++i) {
		for (l j = 1; j <= N; ++j) {
			dp& cur = parent_of[i][j];

			const dp& fx = parent_of[i - 1][j];
			const dp& fxx = parent_of[i - 1][fx.par];

			cur.par = fxx.par;

			//min, max 비교대상f(x), f(f(x))
			cur.min = min(fx.min, fxx.min);
			cur.max = max(fx.max, fxx.max);
		}
	}

	//query
	l K; cin >> K;
	while (K--) {
		l d, e; cin >> d >> e;
		query(d, e);
	}
}