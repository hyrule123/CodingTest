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
백준 11281 (2-SAT 4) [복습][SCC][위상 정렬]
*/
#include <vector>
#include <array>
#include <stack>
#include <queue>
constexpr int graph_MAX = 10000 * 2 + 1;
int N, M;
inline int idx_of(int x) {
	return (0 <= x ? x * 2 : -x * 2 - 1);
}
array<vector<int>, graph_MAX> dir_graph;

int scc_count;
//scc_idx_of[30]: 30번이 몇번 SCC에 속해있는지
array<vector<int>, graph_MAX> scc_member;
array<int, graph_MAX> scc_idx_of;
array<bool, graph_MAX> finished;
stack<int> stk;

int generate_scc(int cur) {
	static int ticket = 0;
	scc_idx_of[cur] = ++ticket;
	stk.push(cur);

	int last_scc = scc_idx_of[cur];
	for (int next : dir_graph[cur]) {
		if (scc_idx_of[next] == 0) {
			last_scc = min(last_scc, generate_scc(next));
		}
		else if (false == finished[next]) {
			last_scc = min(last_scc, scc_idx_of[next]);
		}
	}

	if (last_scc == scc_idx_of[cur]) {
		++scc_count;
		while (true) {
			int member = stk.top(); stk.pop();
			finished[member] = true;
			scc_idx_of[member] = scc_count;

			//SCC '그래프'를 만들기 위해선 각 SCC에 속한 멤버를 모두 아는 상태여야 하는데,
			//그러면 순회를 한번 더 돌아야 하기 때문에 비경제적
			scc_member[scc_count].push_back(member);

			if (cur == member) {
				break;
			}
		}
	}

	return last_scc;
}

vector<vector<int>> scc_graph;
vector<int> scc_indeg;
vector<int> scc_traversal_order;
//위상정렬을 통해 방문순서를 결정
void toposort() {
	scc_graph.resize(scc_count + 1);
	scc_indeg.resize(scc_count + 1);
	scc_traversal_order.resize(scc_count + 1);
	
	//indegree 계산
	for (int from = 1; from <= idx_of(N); ++from) {
		for (int to : dir_graph[from]) {
			if (scc_idx_of[from] == scc_idx_of[to]) { continue; }

			scc_indeg[scc_idx_of[to]]++;
			scc_graph[scc_idx_of[from]].push_back(scc_idx_of[to]);
		}
	}

	queue<int> q;
	for (int i = 1; i <= scc_count; ++i) {
		if (scc_indeg[i] == 0) {
			q.push(i);
		}
	}

	int order = 0;
	while (false == q.empty()) {
		int cur = q.front(); q.pop();

		scc_traversal_order[cur] = ++order;

		for (int next : scc_graph[cur]) {
			scc_indeg[next]--;
			if (scc_indeg[next] == 0) {
				q.push(next);
			}
		}
	}
}

void solve() {
	cin >> N >> M;
	while (M--) {
		int x, y; cin >> x >> y;

		//if not A then B is true
		dir_graph[idx_of(-x)].push_back(idx_of(y));
		dir_graph[idx_of(-y)].push_back(idx_of(x));
	}

	for (int i = 1; i <= idx_of(N); ++i) {
		if (false == finished[i]) {
			generate_scc(i);
		}
	}

	toposort();
	
	auto& ans = finished;
	ans.fill(false);
	bool scc_true = true;
	for (int x = 1; x <= N; ++x) {
		int x_true = idx_of(x), x_false = idx_of(-x);

		//if not x_true then x_false is true
		//if not x_false then x_true is true
		//위 두 조건을 모두 만족해야 하는데 모순이 발생
		if (scc_idx_of[x_true] == scc_idx_of[x_false]) {
			scc_true = false;
			break;
		}

		//if NOT x_true then x_false is true
		if (scc_traversal_order[scc_idx_of[x_true]] < scc_traversal_order[scc_idx_of[x_false]]) {
			ans[x] = false;
		}
		//if NOT x_false then x_true is true
		else {
			ans[x] = true;
		}
	}

	cout << scc_true << '\n';
	if (scc_true) {
		for (int i = 1; i <= N; ++i) {
			cout << ans[i] << ' ';
		}
	}
}