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
struct node {
	bool rest; int atm; vector<int> edges;
};
struct scc_node{
	bool rest; vector<int> members, edges; int deposit, indeg;
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

//위상 정렬과 DP를 동시에 수행
int toposort_n_dp() {
	clearstk();

	//indegree, edge 계산
	for (int n = 1; n <= N; ++n) {
		for (int e : graph[n].edges) {
			int from = scc_ID[n], to = scc_ID[e];
			if (from != to) {
				scc_graph[from].edges.push_back(to);
				scc_graph[to].indeg++;
			}
		}
	}

	//DP, stack init
	vector<int> dp(scc_graph.size());
	int ans = 0;
	for (size_t i = 1; i < scc_graph.size(); ++i) {
		if (scc_graph[i].indeg == 0) {
			stk.push((int)i);
		}
		dp[i] = scc_graph[i].deposit;
	}
	
	bool found = false;
	while (false == stk.empty()) {
		int cur_group = stk.top(); stk.pop();

		//시작점을 찾은 이후부터 계산을 시작한다.
		if (scc_ID[S] == cur_group) {
			found = true;

			if (scc_graph[cur_group].rest) {
				ans = scc_graph[cur_group].deposit;
			}
		}

		for (int next_group : scc_graph[cur_group].edges) {
			if (found) {
				//위상정렬 순서대로 갱신
				//ex) 1->2, 1->3, 2->4, 3->4(다이아몬드 형태)
				dp[next_group] = max(dp[next_group], dp[cur_group] + scc_graph[next_group].deposit);

				//레스토랑이 있는 SCC 노드의 경우 도착조건
				if (scc_graph[next_group].rest) {
					ans = max(ans, dp[next_group]);
				}
			}

			scc_graph[next_group].indeg--;
			if (scc_graph[next_group].indeg == 0) {
				stk.push(next_group);
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

	//위상정렬로 순서를 찾고, 그 순서대로 DP를 계산한다.
	cout << toposort_n_dp();
}