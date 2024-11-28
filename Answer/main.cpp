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
백준 11280 (2-SAT - 3)
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
*/

#include <vector>
#include <stack>
constexpr int INF = 987654321;

int get_x_idx(int i) {
	return (0 <= i ? i * 2 : -i * 2 + 1);
}

vector<vector<int>> graph;
int N, M;

//SCC section
stack<int> stk;
vector<int> scc_idx;
vector<bool> finished;
//vector<vector<int>> sccs;

int build_SCC(int cur) {
	static int id = 0, scc_count = 0;
	scc_idx[cur] = ++id;
	stk.push(cur);

	int ret = scc_idx[cur];
	for (int next : graph[cur]) {
		if (scc_idx[next] == 0) {
			ret = min(ret, build_SCC(next));
		}
		else if (false == finished[next]) {
			ret = min(ret, scc_idx[next]);
		}
	}

	if (scc_idx[cur] == ret) {
		++scc_count;
		//sccs.resize(scc_count + 1);
		//auto& scc = sccs[scc_count];
		while (true) {
			int mem = stk.top(); stk.pop();
			finished[mem] = true;
			scc_idx[mem] = scc_count;
			//scc.push_back(mem);

			if (mem == cur) {
				break;
			}
		}
	}

	return ret;
}

void solve() {
	cin >> N >> M;

	//역을 별도의 노드로 취급->2N개의 노드가 필요
	//시작점: 2
	//1 = 1 * 2(2), NOT 1 = 1 * 2 + 1(3)
	graph.resize((N + 1) * 2 + 1);
	for (int i = 1; i <= M; ++i) {
		int a, b; cin >> a >> b;
		//NOT a->b, NOT b->a
		graph[get_x_idx(-a)].push_back(get_x_idx(b));
		graph[get_x_idx(-b)].push_back(get_x_idx(a));
	}

	//만들어진 그래프를 활용해서 SCC를 생성
	scc_idx.resize(graph.size());
	finished.resize(graph.size());
	for (int i = 2; i < (int)graph.size(); ++i) {
		if (false == finished[i]) {
			build_SCC(i);
		}
	}

	//노드를 순회돌면서 NOT i와 i가 같은 SCC 안에 속하지 않는지 확인한다.
	//만약 단 하나라도 같은 SCC에 들어있을 경우 2-SAT 만족 불가능
	bool ans = true;
	for (int i = 1; i <= N; ++i) {
		if (scc_idx[get_x_idx(i)] == scc_idx[get_x_idx(-i)]) {
			ans = false;
			break;
		}
	}
	cout << ans;
}