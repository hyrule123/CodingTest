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
#include <array>
#include <vector>

constexpr int MAX = 32001;
int N, M;
struct node { 
	int in_degree; 
	vector<int> edges; 
};
array<node, MAX> graph;
priority_queue<int, vector<int>, greater<>> pq;

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		graph[a].edges.push_back(b);
		graph[b].in_degree++;
	}

	for (int i = 1; i <= N; ++i) {
		if(graph[i].in_degree == 0){
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