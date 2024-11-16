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
#include <stack>
constexpr int INVALID = -1;
struct node {
	int in_degree;
	vector<int> edges;

	//순위 교체
	bool swap_rank(int my_idx, int other_idx, node& other) {
		for (int& idx : edges) {
			if (idx == other_idx) {
				idx = INVALID;
				other.edges.push_back(my_idx);
				in_degree++;
				other.in_degree--;
				return true;
			}
		}

		return false;
	}


};

int tc;

void topology_sort(vector<node>& graph) {
	stack<int> stk;
	
	for (size_t i = 1; i < graph.size(); ++i) {
		if (0 == graph[i].in_degree) {
			stk.push((int)i);

			//in degree(시작점)이 2개 이상일 경우 정확한 순위를 알 수 없음.
			if (1 < stk.size()) {
				cout << '?';
				return;
			}
		}
	}

	vector<int> ans; ans.reserve(graph.size());
	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();

		ans.push_back(cur);

		for (int next : graph[cur].edges) {
			if (next == INVALID) { continue; }
			
			graph[next].in_degree--;
			if (graph[next].in_degree == 0) {
				stk.push(next);
			}
		}
	}

	//정렬이 완료되지 못하고 중간에 중단되었을 경우
	if (ans.size() + 1 < graph.size()) {
		cout << "IMPOSSIBLE";
	}
	else {
		for (int i : ans) {
			cout << i << ' ';
		}
	}
}

void solve() {
	cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector<node> graph;
		graph.resize(n + 1);

		vector<int> rank;
		rank.resize(n);
		for (int& r : rank) {
			cin >> r;
		}
		
		//간선 추가(상위 랭크 -> 하위 랭크 노드 전부에 간선 연결)
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				graph[rank[i]].edges.push_back(rank[j]);
				graph[rank[j]].in_degree++;
			}
		}

		int m; cin >> m;
		while (0 < m--) {
			int a, b; cin >> a >> b;

			//순위 교체
			if (false == graph[a].swap_rank(a, b, graph[b])) {
				graph[b].swap_rank(b, a, graph[a]);
			}
		}

		topology_sort(graph);
		cout << '\n';
	}
}