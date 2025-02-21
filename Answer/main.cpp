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
백준 18405(경쟁적 전염) [BFS][v2][4ms]
v1: 각 박테리아 별로 큐 1000개 사용
v2: 굳이 큐를 1000개 써야되나? 인풋에서 받고 정렬한 뒤 큐에 넣으면 되지 않나? -> 맞음
*/
#include <queue>
#include <vector>
#include <algorithm>
struct input { 
	int label; 
	pair<int, int> cod;
	auto operator <=> (const input& o) const
	{
		return label <=> o.label;
	}
};
vector<input> inputs;
queue<pair<int, int>> q[2];
int N, K, S, X, Y, board[201][201];

void solve()
{
	cin >> N >> K;
	inputs.reserve(K);
	for (int r = 1; r <= N; ++r)
	{
		for (int c = 1; c <= N; ++c)
		{
			cin >> board[r][c];
			if (board[r][c] != 0)
			{
				inputs.push_back({ board[r][c], {r, c} });
			}
		}
	}
	//박테리아 번호 순으로 정렬
	sort(inputs.begin(), inputs.end());

	bool cur = 0;
	for (auto cod : inputs)
	{
		q[cur].push(cod.cod);
	}
	cin >> S >> X >> Y;

	//BFS
	while (S)
	{
		S--;
		//이번 큐와 다음 큐를 분리
		while (false == q[cur].empty())
		{
			pair<int, int> cur_cod = q[cur].front(); q[cur].pop();

			//up
			const int R = cur_cod.first, C = cur_cod.second;
			if (1 <= R - 1 && board[R - 1][C] == 0)
			{
				board[R - 1][C] = board[R][C];
				q[!cur].push({ R - 1, C });
			}

			//down
			if (R + 1 <= N && board[R + 1][C] == 0)
			{
				board[R + 1][C] = board[R][C];
				q[!cur].push({ R + 1, C });
			}

			//left
			if (1 <= C - 1 && board[R][C - 1] == 0)
			{
				board[R][C - 1] = board[R][C];
				q[!cur].push({ R, C - 1 });
			}

			//right
			if (C + 1 <= N && board[R][C + 1] == 0)
			{
				board[R][C + 1] = board[R][C];
				q[!cur].push({ R, C + 1 });
			}
		}
		//큐 교체
		cur = !cur;
	}

	cout << board[X][Y];
}