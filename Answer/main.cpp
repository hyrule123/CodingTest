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
백준 4013 (ATM)
A와 B가 Strongly Connected Component라는 건
A에서 출발하던 B에서 출발하던 서로에게 도달할 수 있다는 것
하나의 SCC에서 다른 노드로 얼마든지 갈 수 있으므로
SCC에서 뽑을수 있는 액수와 레스토랑 유무를 뽑아서 묶어놓은 후 길찾기를 하면 될듯
또한 SCC로 새로 그래프를 짤 경우
사이클이 없는 방향 그래프(DAG, Directed Acyclic Graph)가 된다. -> 위상 정렬을 사용할 수 있게 됨

어떤 노드에서 출발해도 하나 이상의 레스토랑에 도착 가능
출발 장소 S 주어짐

*/

#include <vector>
#include <stack>
#include <queue>
struct node {
	bool rest; int atm; vector<int> edges;
};
struct scc_node{
	bool rest; int deposit; vector<int> members, edges;
};
vector<node> graph;
int N, M, S, P, id_temp, scc_idx;
vector<int> scc_ID;
vector<bool> finished;
stack<int> stk;
vector<scc_node> scc_graph;

void clearstk() { while (!stk.empty()) { stk.pop(); } }

int build_SCC(const int cur) {
	scc_ID[cur] = ++id_temp;
	stk.push(cur);
	int ret = scc_ID[cur];
	for (int next : graph[cur].edges) {
		if (scc_ID[next] == 0) {
			ret = min(ret, build_SCC(next));
		}
		else if (false == finished[next]) {
			ret = min(ret, scc_ID[next]);
		}
	}

	if (scc_ID[cur] == ret) {
		scc_node scc{};
		++scc_idx;
		
		while (true) {
			int mem = stk.top(); stk.pop();
			scc_ID[mem] = scc_idx;
			finished[mem] = true;
			scc.members.push_back(mem);
			scc.deposit += graph[mem].atm;
			scc.rest |= graph[mem].rest;

			if (cur == mem) { break; }
		}

		scc_graph.push_back(scc);
	}

	return ret;
}

int BFS() {
	//edge 생성
	for (int i = 1; i <= N; ++i) {
		for (int next : graph[i].edges) {
			if (scc_ID[i] != scc_ID[next]) {
				scc_graph[scc_ID[i]].edges.push_back(scc_ID[next]);
			}
		}
	}

	queue<int> q;
	vector<int> dp(scc_graph.size());
	q.push(scc_ID[S]);
	dp[q.front()] = scc_graph[q.front()].deposit;

	int ans = 0;
	
	while (false == q.empty()) {
		int cur = q.front(); q.pop();

		if (scc_graph[cur].rest) {
			ans = max(ans, dp[cur]);
		}

		for (int next : scc_graph[cur].edges) {
			//새로운 값으로 갱신되면 queue에 넣는다
			if (dp[next] < dp[cur] + scc_graph[next].deposit) {
				dp[next] = dp[cur] + scc_graph[next].deposit;
				q.push(next);
			}
		}
	}

	return ans;
}

void solve() {
	cin >> N >> M;
	graph.resize(N + 1);
	scc_ID.resize(N + 1);
	finished.resize(N + 1);
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		graph[a].edges.push_back(b);
	}
	for (int i = 1; i <= N; ++i) {
		int money; cin >> money;
		graph[i].atm = money;
	}
	cin >> S >> P;
	for (int i = 1; i <= P; ++i) {
		int p; cin >> p;
		graph[p].rest = true;
	}
	
	//SCC를 만든 다음
	scc_graph.resize(1);
	for (int i = 1; i <= N; ++i) {
		if (false == finished[i]) {
			build_SCC(i);
		}
	}
	
	cout << BFS();
}