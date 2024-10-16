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
constexpr int MAX = 1'000'000, exclude = 0, include = 1;

int N;
std::vector<std::vector<int>> nodes;
int dp[MAX][2];

void dp_recursive(int cur, int par) {
	dp[cur][exclude] = 0;
	dp[cur][include] = 1;

	for (int next : nodes[cur]) {
		if (next != par) {
			dp_recursive(next, cur);

			//내가 얼리어댑터가 아니라면 인접 노드는 반드시 얼리어댑터여야 함
			dp[cur][exclude] += dp[next][include];

			//내가 얼리어댑터라면 인접 노드가 얼리어댑터여도 되고 아니어도 됨
			//둘중 작은 값을 적용
			dp[cur][include] += std::min(dp[next][exclude], dp[next][include]);
		}
	}
}

void solve()
{
	std::cin >> N;
	nodes.resize(N + 1);

	//두번째 줄부터 N-1개의 줄에는
	for (int i = 1; i < N; ++i){
		int a, b; std::cin >> a >> b;
		nodes[a].push_back(b);
		nodes[b].push_back(a);
	}
	dp_recursive(1, 0);

	std::cout << std::min(dp[1][exclude], dp[1][include]);
}