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
백준 10282 (해킹) [graph][다익스트라]
* 다익스트라를 사용
*/
#include <vector>
#include <queue>
struct edge
{
	int dest, dist;

	auto operator <=> (const edge& o) const
	{
		return this->dist <=> o.dist;
	}
};

void BFS(const vector<vector<edge>>& graph, int start)
{
	constexpr int INF = (int)1e9 * 2;
	vector<int> dists(graph.size(), INF);
	priority_queue<edge, vector<edge>, greater<>> pq;
	pq.push({ start, 0 });
	dists[start] = 0;

	while (false == pq.empty())
	{
		edge cur = pq.top(); pq.pop();

		for (const auto& next : graph[cur.dest])
		{
			int next_dist = cur.dist + next.dist;
			if (dists[next.dest] > next_dist)
			{
				dists[next.dest] = next_dist;
				pq.push({ next.dest, next_dist });
			}
		}
	}

	int longest = 0, infected = 0;
	for (int i = 1; i < (int)graph.size(); ++i)
	{
		if (dists[i] == INF) { continue; }

		longest = max(longest, dists[i]);
		infected++;
	}

	cout << infected << ' ' << longest << '\n';
}

void solve()
{
	int T; cin >> T;
	while (T--)
	{
		//컴퓨터 개수n, 의존성 개수 d, 해킹당한 컴퓨터 번호 c
		int n, d, c; cin >> n >> d >> c;

		//fst: node, snd: dist
		vector<vector<edge>> graph;
		graph.resize(n + 1);

		for (int i = 0; i < d; ++i)
		{
			//b가 감염되면 s초 후 a도 감염된다.
			int a, b, s; cin >> a >> b >> s;
			graph[b].push_back({ a, s });
		}

		BFS(graph, c);
	}
}