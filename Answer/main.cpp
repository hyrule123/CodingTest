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
백준 11277 (2-SAT - 1)
CNF는 AND로 연결 -> 모든 절은 그래프처럼 연결되어 있음
또한 각 bool 변수들은 여러가지 절에 들어가있을수도 있다 -> 이 때문에 사이클이 생길 수 있다
사이클이 생기게 되면, 사이클 안의 모든 변수들은 서로 논리구조가 연결된다.(SCC 사용이 가능하다는뜻)

논리 관계를 그래프로 만들기
P->Q 간선의 의미: P가 거짓이면 Q는 반드시 true여야 한다는 뜻

참고) 경우의 수
P->Q: NOT P가 bool일때 Q가 bool이라면
1. NOT P = true(P = false) -> Q = true: (false | true) = true
2. NOT P = true(P = false) -> Q = false: (false | false) = false
3. NOT P = false(P = true) -> Q = false: (true | false) = true
4. NOT P = false(P = true) -> Q = true: (true | true) = true

A V B: 둘중 하나는 반드시 true여야 함
A가 F -> B는 반드시 T여야 한다, B가 F -> A는 반드시 T여야 한다 
하나의 조건에 두 가지 간선이 만들어짐. NOT A->B, NOT B->A 두 간선을 그래프에 추가

(A V B)
nA->B
nB->A
2개 간선이 생성

(A V nB) ∧ (B ∧ nA) ^ (A ^ B)
nA->nB
B->A
nB->nA
A->B
nA->B
nB->A
4개 간선이 생성

nA->nB->A라는 사이클이 하나 생성되는데,
여기서 nA->A와 A->nA로 이동이 가능해진다.
nA->A는 곧 NOT NOT A -> A 이므로 위의 예시에서 

케이스가 적어서 단순 DFS와 순열을 활용하여 가능할거 같음
*/

#include <algorithm>
#include <vector>
#define a first
#define b second
using pii = pair<int, int>;

int N, M;
vector<pii> CNF;
vector<bool> comb;

bool get_comb(int i) {
	return (0 <= i ? comb[i] : !comb[-i]);
}

bool check() {
	bool ret = true;

	for (const pii& p : CNF) {
		ret = ret && (get_comb(p.first) || get_comb(p.second));
		if (ret == false) {
			break;
		}
	}

	return ret;
}

void solve() {
	cin >> N >> M;
	
	CNF.reserve(M);
	for (int i = 1; i <= M; ++i) {
		pii p; cin >> p.a >> p.b;
		CNF.push_back(p);
	}

	comb.resize(N + 1);
	for (int i = 1; i <= N + 1; ++i) {
		for (int j = 1; j < i; ++j) {
			comb[j] = true;
		}

		do {
			if(check()) { 
				cout << true;
				return;
			}
		} while (prev_permutation(comb.begin() + 1, comb.end()));
	}

	cout << false;
}