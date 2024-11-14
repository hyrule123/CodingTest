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

#include <vector>
#include <queue>
struct node {
	int in_degree{};
	vector<int> edges;
};

int N, M;
node nodes[32001];

void topology_sort(queue<int>& q, vector<int>& result) {
	while (false == q.empty()) {
		int n = q.front(); q.pop();

		result.push_back(n);

		for (int next : nodes[n].edges) {
			--(nodes[next].in_degree);
			if (0 == nodes[next].in_degree) {
				q.push(next);
			}
		}
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		++(nodes[b].in_degree);	//진입차수를 기록
		nodes[a].edges.push_back(b);
	}

	queue<int> q;
	vector<int> ans;
	for (int i = 1; i <= N; ++i) {
		//진입차수가 0인 노드를 큐에 삽입
		if (0 == nodes[i].in_degree) {
			q.push(i);
		}
	}

	//정렬
	topology_sort(q, ans);

	for (int order : ans) {
		cout << order << ' ';
	}
}