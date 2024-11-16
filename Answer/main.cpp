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

//백준 3584 (가장 가까운 공통 조상) [LCA][브루트포스]
#include <vector>
#include <unordered_set>

struct node {
	int parent = -1;
};
int TC;

void solve() {

	
	cin >> TC;
	while (TC--) {
		int N; cin >> N;
		vector<int> graph;
		graph.resize(N + 1);
		for (int i = 1; i < N; ++i) {
			int par, chd; cin >> par >> chd;
			graph[chd] = par;
		}

		unordered_set<int> parents;
		int a, b; cin >> a >> b;
		while (a != 0) {
			parents.insert(a);
			a = graph[a];
		}

		while (b != 0) {
			auto iter = parents.find(b);
			if (parents.end() != iter) {
				cout << *iter << '\n';
				break;
			}
			b = graph[b];
		}
	}
}