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
백준 3977 (축구 전술)
in_degree를 미리 계산한다.
SCC를 모두 구한다.
구한 SCC에 대해 다시 in degree를 구한다.
만약 in_degree가 두개 이상 0일 경우, confused 출력
그렇지 않을 경우, in_degree가 0인 SCC의 멤버를 정렬해서 출력
*/
#include <vector>
#include <algorithm>
#include <stack>

constexpr int MAX = 100'000;
int N, M, visit_order, scc_count;
stack<int> stk;
vector<int> group_ID;
vector<bool> finished;
vector<vector<int>> graph, sccs;
vector<int> scc_in_degrees;

void resize_N() {
	visit_order = 0;
	scc_count = 0;
	group_ID.clear(); group_ID.resize(N);
	graph.clear(); graph.resize(N);
	finished.clear(); finished.resize(N);

	sccs.clear(); sccs.resize(1);	//scc_group_id는 1부터 사용하므로
	scc_in_degrees.clear();

	while (false == stk.empty()) { stk.pop(); }
}

int SCC_DFS(int cur) {
	group_ID[cur] = ++visit_order;

	stk.push(cur);

	int ret = group_ID[cur];
	for (int next : graph[cur]) {
		if (group_ID[next] == 0) {
			ret = min(ret, SCC_DFS(next));
		}
		else if (false == finished[next]) {
			ret = min(ret, group_ID[next]);
		}
	}

	if (ret == group_ID[cur]) {
		vector<int> scc;
		++scc_count;

		while (true) {
			int member = stk.top(); stk.pop();
			finished[member] = true;
			group_ID[member] = scc_count;

			scc.push_back(member);

			if (member == cur) { break; }
		}

		sort(scc.begin(), scc.end());

		sccs.push_back(scc);
	}

	return ret;
}


void solve() {
	int T; cin >> T;
	while (T--) {
		cin >> N >> M;
		resize_N();
		for (int i = 0; i < M; ++i) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
		}

		for (int i = 0; i < N; ++i) {
			if (false == finished[i]) {
				SCC_DFS(i);
			}
		}

		//in_degree 계산
		scc_in_degrees.resize(scc_count + 1);
		for (int from = 0; from < N; ++from) {
			for (int to : graph[from]) {
				if (group_ID[from] != group_ID[to]) {
					scc_in_degrees[group_ID[to]]++;
				}
			}
		}

		//시작 노드 확인(in degree가 0인 노드가 2개 이상이면 절대로 한번에 연결할 수 없음)
		int start_node = 0;
		for (int i = 1; i <= scc_count; ++i) {
			if (scc_in_degrees[i] == 0) {
				if (start_node != 0) {
					start_node = 0;
					break;
				}
				start_node = i;
			}
		}

		if (start_node == 0) {
			cout << "Confused" << '\n';
		}
		else {
			//scc의 start_node부터 방문하면 차례대로 전부 방문 가능.
			for (int ans : sccs[start_node]) {
				cout << ans << '\n';
			}
		}

		cout << '\n';
	}
}

