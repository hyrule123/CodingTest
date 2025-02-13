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
백준 2098 (외판원 순회) [TSP][DP][복습]

//dp[i][j]
i: bit mask -> 방문한 도시를 1로 표시
2: 마지막에 방문한 도시 -> 순서에 따라서도 달라지므로
*/


constexpr int bit_MAX = 1 << 16, INF = (int)1e9;
int N, inputs[16][16], dp[1 << 16][16];

int TSP(int visited_mask, int to)
{
	//이번 도시를 지나갔다고 체크
	visited_mask |= 1 << to;

	//종료 조건: 모든 도시를 순회 돌았을 경우
	if (visited_mask == (1 << N) - 1)
	{
		//마지막으로 방문한 도시에서 시작 도시(여기서는 0)로 돌아올 수 있는지 확인한다.
		//돌아올 수 없다면 INF를 반환
		return (inputs[to][0] == 0 ? INF : inputs[to][0]);
	}
	
	int& cur = dp[visited_mask][to];

	//아직 계산 안한 경우
	if (cur == -1)
	{
		cur = INF;
		for (int i = 0; i < 16; ++i)
		{
			//출발지 == 목적지
			if (i == to) { continue; }

			//길이 연결되어있지 않은 경우 0(순회 불가)
			if (inputs[to][i] == 0) { continue; }

			//이미 방문한 도시일 경우 스킵
			if (visited_mask & 1 << i) { continue; }

			//이번 도시로부터 i로 가는 방법을 구하고
			//다른 순회 경로에서 방문했던 결과와 비교
			cur = min(cur, TSP(visited_mask, i) + inputs[to][i]);
		}
	}

	return cur;
}

void solve()
{
	memset(dp, -1, sizeof(dp));

	cin >> N;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			cin >> inputs[r][c];
		}
	}

	//미방문(0), 첫 출발지(0)
	cout << TSP(0, 0);
}