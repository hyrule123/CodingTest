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
백준 10282 (해킹) [graph][벨만-포드 썼는데 오답?]
이건 벨만 포드를 써야함
* 참고 - 각 알고리즘 별 최적 사용처
* 다익스트라: 한 노드 -> 다른 한 노드 (가중치가 양수일 때만)
* 플로이드-워셜: 모든 노드 -> 모든 노드 전부 구할때
* 벨만-포드: 한 노드 -> 다른 모든 노드
*/
#include <vector>
#include <queue>
using uint = unsigned int;
struct edge
{
	uint from, to, weight;
};

constexpr uint INF = (uint)1e9 * 2;
void BFS(const vector<edge>& edges, uint node_num, uint start)
{
	vector<uint> dists(node_num + 1, INF);

	dists[start] = 0;
	uint infected = 1;
	
	//e: 건너갈 수 있는 간선의 수(하나씩 늘려감)
	for (uint e_len = 1; e_len <= node_num - 1; ++e_len)
	{
		//모든 간선을 순회
		//e.from을 거쳐서 e.to로 가는 방법을 갱신하는 작업
		for (const edge& e : edges)
		{
			//아직 간선의 출발점을 방문한적 없다면 continue
			if (dists[e.from] == INF) { continue; }
			
			//첫 방문일 경우 감염된 컴퓨터 수를 늘려준다
			if (dists[e.to] == INF) { ++infected; }

			//e.from을 거쳐서 e.to로 이동하는 것이 더 싸게 먹히면 값을 갱신
			if (dists[e.to] > dists[e.from] + e.weight)
			{
				dists[e.to] = dists[e.from] + e.weight;
			}
		}
	}

	//음수 간선이 있을 경우 한번 더 확인하는 과정이 필요하지만, 음수 간선이 없으므로 안해도 됨
	{}

	//가장 먼 노드를 확인(모든 노드까지의 거리가 구해진 후 계산해야 함)
	uint farthest = 0;
	for (uint i = 1; i <= node_num; ++i)
	{
		if (dists[i] != INF)
		{
			farthest = max(farthest, dists[i]);
		}
	}

	cout << infected << ' ' << farthest << '\n';
}

void solve()
{
	uint T; cin >> T;
	while (T--)
	{
		//컴퓨터 개수n, 의존성 개수 d, 해킹당한 컴퓨터 번호 c
		uint n, d, c; cin >> n >> d >> c;

		vector<edge> graph;
		graph.reserve(d);

		for (uint i = 0; i < d; ++i)
		{
			//b가 감염되면 s초 후 a도 감염된다.
			uint a, b, s; cin >> a >> b >> s;
			
			graph.push_back({ b, a, s });
		}

		BFS(graph, n, c);
	}
}