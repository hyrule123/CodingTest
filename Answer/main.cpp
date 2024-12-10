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
백준 16367 (TV Show Game) [그래프][SCC][2-SAT]
*/

#include <vector>
#include <array>
#include <stack>

int lmp_num, ptc_num;
struct choice { int lamp_idx; char color; };

vector<vector<int>> graph;
int idxof(int x) {
	return (0 <= x ? x * 2 : -x * 2 - 1);
}

int id_gen, scc_num;
vector<int> scc_id;
vector<bool> finished;
stack<int> stk;
int build_SCC(int cur) {
	scc_id[cur] = ++id_gen;
	stk.push(cur);

	int result = scc_id[cur];
	for (int next : graph[cur]) {
		if (scc_id[next] == 0) {
			result = min(result, build_SCC(next));
		}
		else if (false == finished[next]) {
			result = min(result, scc_id[next]);
		}
	}

	if (result == scc_id[cur]) {
		++scc_num;

		while (true) {
			int member = stk.top(); stk.pop();
			scc_id[member] = scc_num;
			finished[member] = true;

			if (cur == member) { break; }
		}
	}

	return result;
}

struct SCC {
	int order, indeg;
	vector<int> edges;
};
vector<SCC> scc_graph;
void toposort() {
	while (false == stk.empty()) { stk.pop(); }

	scc_graph.resize(scc_num + 1);
	for (int from = 1; from < (int)graph.size(); ++from) {
		for (int to : graph[from]) {
			int scc_from = scc_id[from], scc_to = scc_id[to];

			if (scc_from != scc_to) {
				scc_graph[scc_from].edges.push_back(scc_to);
				scc_graph[scc_to].indeg++;
			}
		}
	}

	for (int i = 1; i < (int)scc_graph.size(); ++i) {
		if (scc_graph[i].indeg == 0) {
			stk.push(i);
		}
	}

	int order = 0;
	while (false == stk.empty()) {
		int cur = stk.top(); stk.pop();
		scc_graph[cur].order = ++order;

		for (int next : scc_graph[cur].edges) {
			if (0 == --scc_graph[next].indeg) {
				stk.push(next);
			}
		}
	}
}

void solve() {
	cin >> lmp_num >> ptc_num;

	graph.resize(lmp_num * 2 + 1);


	//그래프로 변환
	//램프 A, B, C가 있다고 가정할 때 최소 2개는 맞춰야 하므로
	//A가 오답일 경우 -> 나머지 B, C는 정답이어야 한다
	//NOT A -> B, C
	//NOT B -> A, C
	//NOT C -> A, B
	//총 6가지 간선을 추가한다.
	for (int i = 1; i <= ptc_num; ++i) {
		//3가지 선택을 확인.
		//i가 파란색일 경우 -> i
		//i가 빨간색일 경우 -> -i
		array<int, 3> is_B;
		for (int& cur : is_B) {
			char color;
			cin >> cur >> color;
			if (color != 'B') { cur = -cur; }
		}

		graph[idxof(-is_B[0])].push_back(idxof(is_B[1]));
		graph[idxof(-is_B[0])].push_back(idxof(is_B[2]));
		
		graph[idxof(-is_B[1])].push_back(idxof(is_B[0]));
		graph[idxof(-is_B[1])].push_back(idxof(is_B[2]));

		graph[idxof(-is_B[2])].push_back(idxof(is_B[0]));
		graph[idxof(-is_B[2])].push_back(idxof(is_B[1]));
	}

	//SCC BUILD
	scc_id.resize(graph.size());
	finished.resize(graph.size());
	for (int i = 1; i < finished.size(); ++i) {
		if (false == finished[i]) {
			build_SCC(i);
		}
	}

	//TOPOSORT
	toposort();

	//정답 기록
	bool valid = true;
	auto& is_BLUE = finished;
	is_BLUE.clear(); is_BLUE.resize(lmp_num + 1);
	for (int l = 1; l <= lmp_num; ++l) {
		int l_is_B = idxof(l), l_is_NOT_B = idxof(-l);
		int scc_l_is_B = scc_id[l_is_B], scc_l_is_NOT_B = scc_id[l_is_NOT_B];

		if (scc_l_is_B == scc_l_is_NOT_B) {
			valid = false;
			break;
		}

		//B가 거짓 -> B는 거짓
		if (scc_graph[scc_l_is_B].order < scc_graph[scc_l_is_NOT_B].order) {
			is_BLUE[l] = false;
		}
		//NOT B가 거짓 -> B는 참
		else {
			is_BLUE[l] = true;
		}
	}

	if (false == valid) {
		cout << -1;
	}
	else {
		for (int i = 1; i < (int)is_BLUE.size(); ++i) {
			cout << (is_BLUE[i] ? 'B' : 'R');
		}
	}
}