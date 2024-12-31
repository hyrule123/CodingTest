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
/*
백준 24459 (회로의 저항) [LCA][오답]
리프노드부터 리프노드까지의 거리 중 최장거리와 최단거리 구하기
* 유사 문제: 백준 3176 (도로 네트워크)
* LCA를 사용하여 푸는 문제인가...했으나 아닌 듯
마지막에 리프노드의 모든 쌍끼리 거리를 구하는 과정에서 O(N^2)가 될 수도 있음
*/
#include <vector>
#include <stack>
#include <cmath>
using pii = pair<int, int>;
#define TO first
#define DIST second
#define shortest first
#define longest second
struct parent_info {
	int parent, dist;
};
//2^16 = 65535, 2^17은 해야 10만이 넘음
//binary lifting을 하기 위해선 최소 1 << 17까지는 쓸 수 있어야 하므로 18을 배열의 길이로 준다
constexpr int N_MAX = 100'000, N_MAX_LOG2 = 18;
int N;
vector<pii> graph[N_MAX];
parent_info parent_of[N_MAX][N_MAX_LOG2];
int depth[N_MAX];
vector<int> leaf_nodes;

void build_parent_of() {
	vector<bool> visited; visited.resize(N);
	stack<int> stk;
	stk.push(0);
	visited[0] = true;

	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();

		if (graph[cur].size() == 1) {
			leaf_nodes.push_back(cur);
		}

		for (const pii& next : graph[cur]) {
			if (visited[next.TO]) { continue; }
			visited[next.TO] = true;

			//next의 부모님은 cur,
			//next에서 cur로 가는 최단거리, 최장거리는 DIST
			parent_of[next.TO][0].parent = cur;
			parent_of[next.TO][0].dist = next.DIST;
			depth[next.TO] = depth[cur] + 1;

			stk.push(next.TO);
		}
	}
}

void precompute_parent_of() {
	for (int h = 1; h < N_MAX_LOG2; ++h) {
		for (int i = 0; i < N_MAX; ++i) {
			/*
			i의 1<<h번째 부모
			0은 직계부모(1 << 0)
			1은 1 << 1 = 2 이므로 부모의 부모의 부모
			부모의 부모(1 << 0) 의 부모(1 << 0)
			
			1<<2 는 4 이므로 
			1<<2의 부모의 1<<1번째 부모(a)
			a의 1<<1번쨰 부모를 구하면 됨

			쉽게 말해서 n의 1<<h번쨰 부모를 구하라 라고 하면
			1<<h-1번쨰 부모를 찾고, 그 부모의 1<<h-1번째 부모를 찾으면 되는것이다
			*/
			auto& cur = parent_of[i][h];

			auto& par = parent_of[i][h - 1];
			auto& par_par = parent_of[par.parent][h - 1];

			cur.parent = par_par.parent;
			cur.dist = par.dist + par_par.dist;
		}
	}
}

int query_dist(int a, int b) {
	if (depth[a] > depth[b]) {
		swap(a, b);
	}

	int total_dist = 0;
	int depth_diff = depth[b] - depth[a];
	for (int shifts = 0; shifts < N_MAX_LOG2; ++shifts) {
		int bit = 1 << shifts;
		if (depth_diff < bit) { break; }
		if (depth_diff & bit) {
			total_dist += parent_of[b][shifts].dist;
			b = parent_of[b][shifts].parent;
		}
	}

	//a가 b의 부모 노드였을 경우 리턴
	if (a == b) {
		return total_dist;
	}

	//먼 거리부터 탐색. 공통 조상이 달라지는 처음 부분을 찾는다.
	for (int h = N_MAX_LOG2 - 1; h >= 0; --h) {
		if (parent_of[a][h].parent == parent_of[b][h].parent) {
			continue;
		}

		total_dist += parent_of[a][h].dist;
		total_dist += parent_of[b][h].dist;

		a = parent_of[a][h].parent;
		b = parent_of[b][h].parent;
	}

	//공통 조상이 달라지는 처음 부분을 찾은것이므로 직계 조상까지의 거리도 더해줘야 한다
	total_dist += parent_of[a][0].dist;
	total_dist += parent_of[b][0].dist;

	return total_dist;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int p, q, r; cin >> p >> q >> r;
		graph[p].push_back({ q, r });
		graph[q].push_back({ p, r });
	}

	build_parent_of();
	precompute_parent_of();

	int min_dist = numeric_limits<int>::max(),
		max_dist = numeric_limits<int>::min();
	for (int i = 0; i < (int)leaf_nodes.size(); ++i) {
		for (int j = i + 1; j < (int)leaf_nodes.size(); ++j) {
			int dist = query_dist(leaf_nodes[i], leaf_nodes[j]);
			min_dist = min(min_dist, dist);
			max_dist = max(max_dist, dist);
		}
	}

	cout << max_dist << '\n' << min_dist;
}