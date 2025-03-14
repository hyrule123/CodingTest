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
백준 22868 (산책) [BFS][v2]
-> 쓸데없는 예외 처리 제거
*/
#include <array>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>

int N, M, S, E, parent[10001], dist_S2E;
array<vector<int>, 10001> graph;
queue<pair<int, int>> q;
bitset<10001> visited;

void find_path()
{
	q.push({ 0, S });
	visited[S] = true;
	while (false == q.empty())
	{
		auto [dist, cur] = q.front(); q.pop();

		if (cur == E)
		{
			stack<int> trace;
			int t = cur;
			while (t != S)
			{
				trace.push(t);
				t = parent[t];
			}
			trace.push(t);

			dist_S2E = (int)trace.size() - 1;

			//방문처리
			visited.reset();
			while (false == trace.empty())
			{
				visited[trace.top()] = true;
				trace.pop();
			}
			return;
		}

		for (int next : graph[cur])
		{
			if (visited[next]) { continue; }
			visited[next] = true;

			parent[next] = cur;

			q.push({ dist + 1, next });
		}
	}
}

void solve()
{
	cin >> N >> M;

	for (int i = 1; i <= M; ++i)
	{
		int A, B; cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}
	cin >> S >> E;

	//예외처리: 출발점 = 도착점
	if (S == E)
	{
		cout << 0;
		return;
	}

	//사전순 최단거리를 찾아야 하므로 노드를 오름차순 정렬
	for (auto& g : graph)
	{
		sort(g.begin(), g.end());
	}

	//S -> E 최단거리를 찾고 
	find_path();

	//큐 초기화하고
	while (false == q.empty()) { q.pop(); }

	//E -> S BFS 길찾기를 수행
	q.push({ 0, E });

	while (false == q.empty())
	{
		auto [dist, cur] = q.front(); q.pop();

		for (int next : graph[cur])
		{
			//도착했을 경우 결과를 출력
			if (next == S)
			{
				cout << dist_S2E + dist + 1;
				return;
			}

			if (visited[next]) { continue; }

			visited[next] = true;
			q.push({ dist + 1, next });
		}
	}
}