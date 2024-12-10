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
백준 3648 (아이돌) [SCC][위상정렬][복습]
*/
#include <vector>
#include <stack>
int n, m;

//not A = -A
//if -A, then -A * 2 - 1
//if A, then A * 2
int idx(int x) {
	return (0 <= x ? x * 2 : -x * 2 - 1);
}
vector<vector<int>> graph;

int scc_num, scc_id_gen;
vector<int> scc_id;
vector<bool> scc_finished;
stack<int> stk;
int build_SCC(int cur) {
	scc_id[cur] = ++scc_id_gen;
	stk.push(cur);

	int result = scc_id[cur];
	for (int next : graph[cur]) {
		if (scc_id[next] == 0) {
			result = min(result, build_SCC(next));
		}
		else if (false == scc_finished[next]) {
			result = min(result, scc_id[next]);
		}
	}

	if (result == scc_id[cur]) {
		++scc_num;
		
		while (true) {
			int member = stk.top(); stk.pop();
			scc_id[member] = scc_num;
			scc_finished[member] = true;
			
			if (cur == member) { break; }
		}
	}

	return result;
}

void solve() {
	while (cin >> n >> m) {
		graph.clear(); graph.resize(n * 2 + 1);
		while (false == stk.empty()) { stk.pop(); }

		while (m--) {
			int a, b; cin >> a >> b;

			//CNF 식을 그래프 형태로 변경
			//NOT A -> B: NOT A가 참이면, B는 참이여야 한다.
			//NOT B -> A: NOT B가 참이면, A는 참이어야 한다.
			graph[idx(-a)].push_back(idx(b));
			graph[idx(-b)].push_back(idx(a));
		}

		//상근이(1번)을 무조건 true로 만드는 CNF 식을 하나 추가한다.
		//1 V 1 == NOT 1 -> 1
		graph[idx(-1)].push_back(idx(1));

		//SCC build
		scc_id.clear(); scc_id.resize(graph.size());
		scc_finished.clear(); scc_finished.resize(graph.size());
		while (false == stk.empty()) { stk.pop(); };
		scc_num = scc_id_gen = 0;

		for (int i = 1; i < (int)scc_finished.size(); ++i) {
			if(false == scc_finished[i]) {
				build_SCC((int)i);
			}
		}

		//같은 SCC 안에 NOT i와 i가 동시에 존재하면 false
		bool valid = true;
		for (int i = 1; i <= n; ++i) {
			if (scc_id[idx(-i)] == scc_id[idx(i)]) {
				valid = false;
				break;
			}
		}

		cout << (valid ? "yes\n" : "no\n");
	}
}