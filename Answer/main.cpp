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
백준 10282 (해킹) [graph][오답]
Djikstra로 전부 순회해야 하므로 오히려 더 오래 걸리는 듯
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
	pq.push({start, 0});
	int last_dist = dists[start] = 0;
	int infected = 1;

	while (false == pq.empty())
	{
		edge cur = pq.top(); pq.pop();

		for (const auto& next : graph[cur.dest])
		{
			int next_dist = cur.dist + next.dist;
			if (dists[next.dest] < next_dist) { continue; }

			//첫 방문일 시 감염 카운트를 1 증가
			if (dists[next.dest] == INF)
			{
				++infected;
			}

			dists[next.dest] = next_dist;
			last_dist = next_dist;

			pq.push({ next.dest, next_dist });
		}
	}

	cout << infected << ' ' << last_dist << '\n';
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