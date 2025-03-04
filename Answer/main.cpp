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
백준 15573 (채굴) [BFS]
*/
#include <queue>
constexpr int INF = (int)0x7c7c7c7c;
int N, M, K, blocks[1001][1001], dig_count, cur_drill_level;

struct elem
{
	int block_level, r, c;

	auto operator <=> (const elem& o) const
	{
		return block_level <=> o.block_level;
	}
};

priority_queue<elem, vector<elem>, greater<>> pq;

void solve()
{
	memset(blocks, 0x7c, sizeof(blocks));

	cin >> N >> M >> K;

	for (int r = 1; r <= N; ++r)
	{
		for (int c = 1; c <= M; ++c)
		{
			cin >> blocks[r][c];
		}
	}

	//공기와 맞닿은 3면을 집어넣어 준다. + 방문처리
	for (int r = 1; r <= N; ++r)
	{
		pq.push({ blocks[r][1], r, 1 });
		blocks[r][1] = INF;

		pq.push({ blocks[r][M], r, M });
		blocks[r][M] = INF;
	}
	for (int c = 1; c <= M; ++c)
	{
		pq.push({ blocks[1][c], 1, c });
		blocks[1][c] = INF;
	}

	//BFS
	while (false == pq.empty())
	{
		elem e = pq.top(); pq.pop();
		
		++dig_count;

		//가장 낮은 레벨의 블록이 현재 곡괭이 레벨보다 높을경우 한단계 올려준다
		cur_drill_level = max(cur_drill_level, e.block_level);

		//목표 채굴 갯수 도달 시 현재 레벨을 출력
		if (K <= dig_count)
		{
			cout << cur_drill_level;
			return;
		}

		//4방향으로 탐색, 채굴하지 않은 블록을 등록
		if (1 <= e.r - 1 && blocks[e.r - 1][e.c] != INF)
		{
			pq.push({ blocks[e.r - 1][e.c] , e.r - 1, e.c });
			blocks[e.r - 1][e.c] = INF;
		}
		if (N >= e.r + 1 && blocks[e.r + 1][e.c] != INF)
		{
			pq.push({ blocks[e.r + 1][e.c] , e.r + 1, e.c });
			blocks[e.r + 1][e.c] = INF;
		}


		if (1 <= e.c - 1 && blocks[e.r][e.c - 1] != INF)
		{
			pq.push({ blocks[e.r][e.c - 1] , e.r, e.c - 1 });
			blocks[e.r][e.c - 1] = INF;
		}
		if (M >= e.c + 1 && blocks[e.r][e.c + 1] != INF)
		{
			pq.push({ blocks[e.r][e.c + 1] , e.r, e.c + 1 });
			blocks[e.r][e.c + 1] = INF;
		}
	}
	
	//여기까지 올 일은 없긴 함
	cout << cur_drill_level;
}