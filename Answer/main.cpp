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
#include <queue>
struct node {
	int in_degree;
	vector<int> edges;
};


array<node, 32001> graph;
int n, m;

void topology_sort() {
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 1; i <= n; ++i) {
		if (graph[i].in_degree == 0) {
			pq.push(i);
		}
	}

	while (false == pq.empty()) {
		int cur = pq.top(); pq.pop();

		cout << cur << ' ';

		for (int next : graph[cur].edges) {
			graph[next].in_degree--;
			if (graph[next].in_degree == 0) {
				pq.push(next);
			}
		}
	}
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int a, b; cin >> a >> b;
		graph[a].edges.push_back(b);
		graph[b].in_degree++;
	}

	topology_sort();
}