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
백준 3648 (아이돌) [SCC][위상정렬]
심사위원 한 명이 두 명에게 투표 -> 반대(NOT), 찬성 -> 둘중 최소 한표는 유효해야 하므로 OR
그냥 2-SAT 문제를 해결했을 때 상근이(1번)이 true인지를 보면 되나?
-> 상근이를 true로 만드는 조건을 CNF식에 추가하면 된다.(X1 V X1)
그러면 그래프에는 NOT X1 -> X1 간선이 추가됨
*/
#include <vector>
#include <stack>
#include <bitset>
#include <string>
constexpr int n_MAX = 2001;
int n, m, node_num;
int x_idx(int x) {
	return (0 <= x ? x * 2 : -x * 2 - 1);
}
stack<int> stk;
vector<int> graph[n_MAX];

//SCC section
int scc_count, temp_id;
int scc_id[n_MAX];
bitset<n_MAX> finished;

int DFS(int cur_idx) {
	scc_id[cur_idx] = ++temp_id;
	stk.push(cur_idx);

	int ret = scc_id[cur_idx];
	for (int next_idx : graph[cur_idx]) {
		if (0 == scc_id[next_idx]) {
			ret = min(ret, DFS(next_idx));
		}
		else if (false == finished[next_idx]) {
			ret = min(ret, scc_id[next_idx]);
		}
	}

	if (ret == scc_id[cur_idx]) {
		++scc_count;

		while (true) {
			int mem = stk.top(); stk.pop();
			finished[mem] = true;
			scc_id[mem] = scc_count;

			if (cur_idx == mem) { break; }
		}
	}

	return ret;
}
void build_scc() {
	memset(scc_id, 0, sizeof(scc_id));
	finished.reset();
	scc_count = temp_id = 0;
	while (false == stk.empty()) { stk.pop(); }

	for (int i = 1; i <= node_num; ++i) {
		if (false == finished[i]) {
			DFS(i);
		}
	}
}

vector<vector<int>> scc_edges;
vector<int> scc_indeg, scc_order;
void toposort() {
	scc_edges.clear(); scc_edges.resize(scc_count + 1);
	scc_indeg.clear(); scc_indeg.resize(scc_count + 1);
	for (int from = 1; from <= node_num; ++from) {
		for (int to : graph[from]) {
			int scc_from = scc_id[from], scc_to = scc_id[to];
			if (scc_from != scc_to) {
				scc_edges[scc_from].push_back(scc_to);
				scc_indeg[scc_to]++;
			}
		}
	}

	while (false == stk.empty()) { stk.pop(); }
	for (int i = 1; i <= scc_count; ++i) {
		if (scc_indeg[i] == 0) {
			stk.push(i);
		}
	}

	scc_order.clear(); scc_order.resize(scc_count + 1);
	int order = 0;
	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();

		scc_order[cur] = ++order;

		for (int next : scc_edges[cur]) {
			if (0 == --(scc_indeg[next])) {
				stk.push(next);
			}
		}
	}
}

void solve() {
	while (cin >> n >> m) {
		node_num = n * 2;

		for (int i = 1; i <= node_num; ++i) {
			graph[i].clear();
		}

		//1번 노드는 반드시 true가 되어야 함 -> (X1 V X1) 조건을 추가. X1이 false 일시 false가 됨
		//그래프로는 NOT X1 -> X1
		graph[x_idx(-1)].push_back(x_idx(1));
		while (m--) {
			int a, b; cin >> a >> b;
			graph[x_idx(-a)].push_back(x_idx(b));
			graph[x_idx(-b)].push_back(x_idx(a));
		}

		build_scc();
		toposort();

		auto& ans_x = finished;
		ans_x.reset();

		bool valid = true;
		for (int x = 1; x <= n; ++x) {
			int X = x_idx(x), NOT_X = x_idx(-x);
			int scc_X = scc_id[X], scc_NOT_X = scc_id[NOT_X];

			if (scc_X == scc_NOT_X) {
				valid = false;
				break;
			}
		}

		cout << (valid ? "yes\n" : "no\n");
	}
}