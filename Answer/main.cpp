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
constexpr int MAX = 100'001;
int N, M, id, scc_id;
vector<vector<int>> graph;
vector<int> scc_indegrees;
vector<bool> finished;
vector<int> ID;

stack<int> stk;
int DFS(int cur) {
	ID[cur] = ++id;

	int last_id = ID[cur];
	stk.push(cur);
	for (int next : graph[cur]) {
		if (ID[next] == 0) {
			last_id = min(last_id, DFS(next));
		}
		else if (false == finished[next]) {
			last_id = min(last_id, ID[next]);
		}
	}

	if (ID[cur] == last_id) {
		++scc_id;
		while (true) {
			int last = stk.top(); stk.pop();

			//몇 번쨰 SCC에 속하는지를 (더이상 사용하지 않는)ID 배열에 저장한다.
			ID[last] = scc_id;

			finished[last] = true;
			if (cur == last) { break; }
		}
	}

	return last_id;
}

void solve() {
	int TC; cin >> TC;
	while (TC--) {
		cin >> N >> M;
		
		id = 0;
		scc_id = 0;
		graph.clear();
		scc_indegrees.clear();
		finished.clear();
		ID.clear();
		graph.resize(N + 1);
		scc_indegrees.resize(graph.size());
		finished.resize(graph.size());
		ID.resize(graph.size());

		for (int i = 0; i < M; ++i) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
		}

		for (int i = 1; i <= N; ++i) {
			if (false == finished[i]) {
				DFS(i);
			}
		}

		scc_indegrees.clear();
		scc_indegrees.resize(scc_id + 1);
		for (int cur = 1; cur <= N; ++cur) {
			for (int next : graph[cur]) {
				//그룹이 다를 경우 해당 그룹의 in_degree를 늘려준다.
				if (ID[cur] != ID[next]) {
					scc_indegrees[ID[next]]++;
				}
			}
		}

		//in_degree가 0인 scc로부터 시작하면 가장 적은 횟수로 도달 가능.
		int count{};
		for (size_t i = 1; i < scc_indegrees.size(); ++i) {
			if (scc_indegrees[i] == 0) {
				++count;
			}
		}
		cout << count << '\n';
	}
}