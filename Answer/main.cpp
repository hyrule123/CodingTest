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
#include <algorithm>
constexpr int MAX = 10001;
int V, E;
vector<int> graph[MAX];
stack<int> stk;
int parent_of[MAX], visit_order[MAX], order;
bool finished[MAX];
vector<vector<int>> answers;

//리턴값: 방문 순서
int DFS(int cur) {
	visit_order[cur] = ++order;
	stk.push(cur);

	int result = visit_order[cur];
	for (int next : graph[cur]) {
		//아직 미방문 정점일 경우(방문 순서가 입력되지 않았을 경우) DFS
		if (visit_order[next] == 0) {
			result = min(result, DFS(next));
		}
		//이미 방문한 정점이지만 SCC 확인이 완료되지 않은 경우: 둘중 작은 값을 반환한다
		else if (false == finished[next]) {
			result = min(result, visit_order[next]);
		}
	}

	//사이클을 발견한 경우 하나의 SCC가 형성된 것
	//visit_order을 위에서 1을 넣었는데, 한바퀴 돌아서 1이 반환된 경우
	//또는 아예 사이클 없이 동떨어져 있는 노드일 경우
	if (result == visit_order[cur]) {
		vector<int> ans;
		while (true) {
			int scc = stk.top(); stk.pop();
			ans.push_back(scc);
			finished[scc] = true;
			if (cur == scc) { break; }
		}
		sort(ans.begin(), ans.end());
		answers.push_back(ans);
	}

	return result;
}

void solve() {
	memset(parent_of, -1, sizeof(parent_of));
	cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
	}
	for (int i = 1; i <= V; ++i) {
		sort(graph[i].begin(), graph[i].end());
	}

	//SCC 확인이 완료되지 않은 정점에 대해 DFS를 수행
	for (int i = 1; i <= V; ++i) {
		if (false == finished[i]) {
			DFS(i);
		}
	}

	sort(answers.begin(), answers.end(),
		[](const vector<int>& a, const vector<int>& b)->bool {
			return a[0] < b[0];
		}
		);
	cout << answers.size() << '\n';
	for (const auto& ans : answers) {
		for (int e : ans) {
			cout << e << ' ';
		}
		cout << -1 << '\n';
	}
}