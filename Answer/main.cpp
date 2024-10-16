#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <stack>
#include <algorithm>
struct node { 
	int weight; 
	std::vector<int> link;
};

//이 노드를 가냐 안가냐로 구분
std::vector<node> graph;
int n, dp[10001][2];
#define EXCLUDE 0
#define INCLUDE 1
std::vector<int> included;

void dp_recursive(int cur, int parent) {
	//나를 포함시킬건지 말건지
	dp[cur][INCLUDE] = graph[cur].weight;
	dp[cur][EXCLUDE] = 0;

	//연결된 노드 순회
	for (int n : graph[cur].link) {
		//'트리'이므로 사이클 없음. 역방향 진행만 검사
		if (parent == n) { continue; }

		dp_recursive(n, cur);
		//미포함으로 결정했을 경우 다음 노드는 가도 되고 안가도 됨. 둘중 높은 값을 선택
		dp[cur][EXCLUDE] += std::max(dp[n][EXCLUDE], dp[n][INCLUDE]);

		//이번 노드를 포함시킬 경우 다음 노드는 포함시킬수 없다.
		dp[cur][INCLUDE] += dp[n][EXCLUDE];
	}
}

//par_sel: 부모 노드의 선택(포함 or 미포함)
void back_trace(int cur, int parent, int par_sel) {
	int cur_sel = -1;

	//부모 노드 미포함일시
	if (par_sel == EXCLUDE) {
		//포함했을 경우와 그렇지 않을 경우 중 큰 값을 선택
		if (dp[cur][EXCLUDE] < dp[cur][INCLUDE]) {
			//포함되었을 경우 인덱스를 답지에 집어넣는다.
			included.push_back(cur);
			cur_sel = INCLUDE;
		}
		else {
			cur_sel = EXCLUDE;
		}
	}
	else {
		cur_sel = EXCLUDE;
	}

	//이번 선택 결과를 재귀 호출
	for (int i : graph[cur].link) {
		if (parent == i) { continue; }
		back_trace(i, cur, cur_sel);
	}
}

void solve() {
	std::cin >> n;
	graph.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> graph[i].weight;
	}

	int a, b;
	while (std::cin >> a >> b) {
		graph[a].link.push_back(b);
		graph[b].link.push_back(a);
	}
	//1번을 루트노드라고 가정하고 재귀 dp를 진행
	dp_recursive(1, 0);

	//루트 노드의 부모노드(없음)은 미포함으로 가정
	back_trace(1, 0, EXCLUDE);

	std::cout << std::max(dp[1][INCLUDE], dp[1][EXCLUDE]) << '\n';

	std::sort(included.begin(), included.end());
	for (int i : included) {
		std::cout << i << ' ';
	}
}