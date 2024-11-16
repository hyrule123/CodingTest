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
#include <array>
#include <stack>

struct node {
	int in_degree;
	vector<int> edges;
};

int N, M;
array<node, 32001> nodes;
stack<int> stk;

//백준 2252 (줄 세우기): 스택 사용
//큐 사용 시: 4272kb/24ms
//스택 사용 시: 4080kb/24ms
//메모리를 좀 덜 먹는다
void topology_sort() {
	for (int i = 1; i <= N; ++i) {
		if (nodes[i].in_degree == 0) {
			stk.push(i);
		}
	}

	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();

		cout << cur << ' ';

		for (int next : nodes[cur].edges) {
			nodes[next].in_degree--;
			if (nodes[next].in_degree == 0) {
				stk.push(next);
			}
		}
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		nodes[a].edges.push_back(b);
		nodes[b].in_degree++;
	}



	topology_sort();
}