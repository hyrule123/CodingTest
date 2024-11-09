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

#include <queue>

struct edge {
	int to, dist;
	bool operator < (const edge& o) const { return dist > o.dist; }
};

int N, E, v1, v2;
vector<edge> edges[801];
priority_queue<edge> pq;
int memo[801];
constexpr int INF = numeric_limits<int>::max();

//from으로부터 모든 노드 사이의 거리를 계산
void djikstra(int from) {
	//기본 container로 vector 사용하므로 재사용
	while (false == pq.empty()) {
		pq.pop();
	}
	for (int& i : memo) {
		i = INF;
	}

	pq.push({ from, 0 });
	memo[from] = 0;

	while (false == pq.empty()) {
		edge t = pq.top(); pq.pop();

		for (const edge& next : edges[t.to]) {
			int next_dist = t.dist + next.dist;

			//삽입 조건 확인
			if (memo[next.to] > next_dist) {
				memo[next.to] = next_dist;
				pq.push({ next.to, next_dist });
			}
		}
	}
}

//1->v1 v1->v2 v2->N, N->v1 v1->v2 v2->N
void solve() {
	cin >> N >> E;
	for (int i = 0; i < E; ++i) {
		int a, b, c; cin >> a >> b >> c;
		edges[a].push_back({ b, c });
		edges[b].push_back({ a, c });
	}
	cin >> v1 >> v2;

	djikstra(v1);
	int
		v1_1 = memo[1],
		v1_N = memo[N],
		v1_v2 = memo[v2];

	djikstra(v2);
	int
		v2_1 = memo[1],
		v2_N = memo[N];

	int path_1 = -1, path_2 = -1;

	if (v1_v2 == INF) {
		cout << -1;
		return;
	}

	if (INF != v1_1 && INF != v2_N) {
		path_1 = v1_1 + v1_v2 + v2_N;
	}
	if (INF != v2_1 && INF != v1_N) {
		path_2 = v2_1 + v1_v2 + v1_N;
	}

	if (path_1 == -1) { cout << path_2; }
	else if (path_2 == -1) { cout << path_1; }
	else {
		cout << (path_1 < path_2 ? path_1 : path_2);
	}
}