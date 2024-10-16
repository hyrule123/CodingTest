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
int N;
struct node {
	int weight;
	std::vector<int> link;
};
std::vector<node> nodes;
int dp[10001][2];
constexpr int exclude = 0, include = 1;

void recursive_DP(int cur, int par) {
	dp[cur][exclude] = 0;
	dp[cur][include] = nodes[cur].weight;

	for (int next : nodes[cur].link) {
		if (next != par) {
			recursive_DP(next, cur);

			//조건 3: 선정되지 못한 마을에 경각심을 불러일으키기 위해서, '우수 마을'로 선정되지 못한 마을은 적어도 하나의 '우수 마을'과는 인접해 있어야 한다.
			// -> 우수마을 인구수가 최대값이 되기 위해서는 연결 노드 중 최소 한개는 우수마을이여야 함.
			dp[cur][exclude] += std::max(dp[next][exclude], dp[next][include]);
			dp[cur][include] += dp[next][exclude];
		}
	}
}

void solve()
{
	std::cin >> N;
	nodes.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		std::cin >> nodes[i].weight;
	}
	for (int i = 1; i <= N - 1; ++i) {
		int a, b; std::cin >> a >> b;
		nodes[a].link.push_back(b);
		nodes[b].link.push_back(a);
	}
	
	recursive_DP(1, 0);
	std::cout << std::max(dp[1][exclude], dp[1][include]);
}