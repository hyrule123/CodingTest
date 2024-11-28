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
백준 11281 (2-SAT - 4)
CNF는 AND로 연결 -> 모든 절은 그래프처럼 연결되어 있음
또한 각 bool 변수들은 여러가지 절에 들어가있을수도 있다 -> 이 때문에 사이클이 생길 수 있다
사이클이 생기게 되면, 사이클 안의 모든 변수들은 서로 논리구조가 연결된다.(SCC 사용이 가능하다는뜻)

* 논리 관계를 그래프로 만들기
P->Q 간선의 의미: "P가 거짓이면 Q는 반드시 true이다"
A V B
A가 거짓이면 B는 반드시 true여야 함
B가 거짓이면 A는 반드시 true여야 함


* 참고) 경우의 수
P->Q: NOT P가 bool일때 Q가 bool이라면
1. NOT P = true(P = false) -> Q = true: (false | true) = true
2. NOT P = true(P = false) -> Q = false: (false | false) = false
3. NOT P = false(P = true) -> Q = false: (true | false) = true
4. NOT P = false(P = true) -> Q = true: (true | true) = true
* 요약
P->Q
T  T: T
T  F: F
F  T: T
F  F: T

* (A V B)
nA->B
nB->A
2개 간선이 생성

* (A V nB) ∧ (B ∧ nA) ^ (A ^ B)
nA->nB
B->A
nB->nA
A->B
nA->B
nB->A
6개 간선이 생성

nA->nB->A라는 사이클이 하나 생성되는데,
이러면 nA->A와 A->nA 두 연결이 생기게 된다.

nA->A = NOT A가 거짓이면(A = true) A는 참이여야 한다
->A = true일 때 성립

A->nA = A = A가 거짓이면 NOT A는 참이어야 한다
->A = false일 때 성립

근데 만약 한 SCC에 두 간선이 모두 존재한다면?
A가 true일 때는 nA->A는 성립하지만 A->nA는 성립 불가
A가 false일 때는 A->nA는 성립하지만 nA->A는 성립 불가 
모순이 발생하므로 주어진 2-CNF는 2-SAT를 충족시킬 수 없다 

여기서 추가로 각 변수의 bool값을 확인하고자 한다면
SCC를 위상정렬해서 SCC 방문 순서를 알아내야 한다.
Xi를 NOT Xi보다 먼저 방문하게 되면 Xi->NOT Xi 연결이 생성된다.
Xi가 거짓이라면, NOT Xi는 참이다. 라는 조건을 참으로 만들기 위한 Xi는 false 이다.

만약 NOT Xi를 Xi보다 먼저 방문한다면 NOT Xi->Xi 연결이 생성된다.
NOT Xi가 거짓이라면 Xi는 참이다. 라는 조건을 참으로 만들기 위한 Xi는 true이다.

이를 통해 각 Xi가 어떤 bool값을 가지는지를 선형 시간 안에 구할 수 있게 된다.
시간 복잡도: O(V+E)
*/

#include <vector>
#include <stack>
int N, M;
vector<vector<int>> graph;
int get_idx(int x) {
	//Xi = 2 -> NOT Xi = 3, Xi = 4
	return (0 <= x ? x * 2 : -x * 2 - 1);
}

//SCC Section
int scc_size;
vector<bool> finished;
stack<int> stk;
vector<int> scc_ID;
vector<vector<int>> sccs;

int SCC_DFS(int cur) {
	static int id_gen = 0;
	scc_ID[cur] = ++id_gen;
	stk.push(cur);

	int ret = scc_ID[cur];
	for (int next : graph[cur]) {
		if (scc_ID[next] == 0) {
			ret = min(ret, SCC_DFS(next));
		}
		else if (false == finished[next]) {
			ret = min(ret, scc_ID[next]);
		}
	}

	if (ret == scc_ID[cur]) {
		++scc_size;
		sccs.resize(scc_size + 1);
		auto& scc = sccs[scc_size];
		while (true) {
			int mem = stk.top(); stk.pop();
			finished[mem] = true;
			scc_ID[mem] = scc_size;
			scc.push_back(mem);

			if (mem == cur) { break; }
		}
	}
	return ret;
}

void build_SCC() {
	finished.resize(graph.size());
	scc_ID.resize(graph.size());

	for (int i = 1; i < (int)graph.size(); ++i) {
		if (finished[i] == false) {
			SCC_DFS(i);
		}
	}
}

vector<int> scc_indeg, scc_order;
vector<vector<int>> scc_edges;
void toposort() {
	scc_indeg.resize(sccs.size());
	scc_edges.resize(sccs.size());
	for (int from = 1; from < graph.size(); ++from) {
		for (int to : graph[from]) {
			int scc_from = scc_ID[from], scc_to = scc_ID[to];
			if (scc_from != scc_to) {
				scc_edges[scc_from].push_back(scc_to);
				scc_indeg[scc_to]++;
			}
		}
	}

	while (!stk.empty()) { stk.pop(); }
	for (int i = 1; i < (int)scc_indeg.size(); ++i) {
		if (scc_indeg[i] == 0) {
			stk.push(i);
		}
	}
	
	//방문 순서를 기록
	scc_order.resize(sccs.size());
	int order = 0;
	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();
		scc_order[cur] = ++order;
		for (int next : scc_edges[cur]) {
			scc_indeg[next]--;
			if (scc_indeg[next] == 0) {
				stk.push(next);
			}
		}
	}
}

void solve() {
	cin >> N >> M;

	graph.resize(N * 2 + 1);
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		graph[get_idx(-a)].push_back(get_idx(b));
		graph[get_idx(-b)].push_back(get_idx(a));
	}

	build_SCC();
	toposort();

	auto& ans = finished;
	ans.clear(); ans.resize(N + 1);
	for (int X = 1; X <= N; ++X) {
		int X_idx = get_idx(X), nX_idx = get_idx(-X);
		if (scc_ID[X_idx] == scc_ID[nX_idx]) {
			cout << 0;
			return;
		}

		//X -> NOT X: X가 거짓이면 NOT X는 참이여야 한다: X = false
		if (scc_order[scc_ID[X_idx]] < scc_order[scc_ID[nX_idx]]) {
			ans[X] = false;
		}
		//NOT X -> X: NOT X가 거짓이면 X는 참이여야 한다: X = true
		else {
			ans[X] = true;
		}
	}

	cout << 1 << '\n';
	for (int i = 1; i <= N; ++i) {
		cout << ans[i] << ' ';
	}
}
