#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;
void solve();
int main()
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

/*
백준 14657(준오는 최종인재야!!) [그래프]
visited 안 쓴 v2
*/

#include <vector>
#include <cmath>
double T;
int N, farthest_node = -1, farthest_node_count = -1, farthest_weighted = -1;
vector<vector<pair<int, int>>> graph;

void DFS(int cur, int prev, int acc_node_count, int acc_weighted)
{
	//노드 개수가 많을 경우 무조건 갱신
	if (farthest_node_count < acc_node_count)
	{
		farthest_node = cur;
		farthest_node_count = acc_node_count;
		farthest_weighted = acc_weighted;
	}
	//노드 갯수는 동일하나 거리가 더 짧을 경우(더 적은 시간으로 더 많은 문제)
	else if (farthest_node_count == acc_node_count 
		&& acc_weighted < farthest_weighted)
	{
		farthest_node = cur;
		farthest_weighted = acc_weighted;
	}

	for (const auto& edge : graph[cur])
	{
		if (edge.first == prev) { continue; }
		DFS(edge.first, cur, acc_node_count + 1, acc_weighted + edge.second);
	}
}

void solve()
{
	cin >> N >> T;
	graph.resize(N + 1);
	
	for (int i = 0; i < N - 1; ++i)
	{
		int a, b, c; cin >> a >> b >> c;
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}


	DFS(1, 0, 0, 0);
	int farthest_a = farthest_node;

	farthest_node_count = farthest_node = farthest_weighted = -1;
	DFS(farthest_a, 0, 0, 0);

	cout << (int)ceil((double)farthest_weighted / T);
}
