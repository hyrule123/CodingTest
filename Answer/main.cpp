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
백준 18405(경쟁적 전염) [BFS][v1][628ms]
*/
#include <queue>
queue<pair<int, int>> qs[1001];
int N, K, S, X, Y, board[201][201];

void solve()
{
	cin >> N >> K;
	for (int r = 1; r <= N; ++r)
	{
		for (int c = 1; c <= N; ++c)
		{
			cin >> board[r][c];
			if (board[r][c] != 0)
			{
				qs[board[r][c]].push({ r, c });
			}
		}
	}
	cin >> S >> X >> Y;

	//BFS
	while (S)
	{
		S--;
		for (int i = 1; i <= K; ++i)
		{
			queue<pair<int, int>> new_q;
			//이번 큐에 있는거 다 쓰고
			while (false == qs[i].empty())
			{
				pair<int, int> cur_cod = qs[i].front(); qs[i].pop();

				//up
				const int R = cur_cod.first, C = cur_cod.second;
				if (1 <= R - 1 && board[R - 1][C] == 0)
				{
					board[R - 1][C] = i;
					new_q.push({ R - 1, C });
				}

				//down
				if (R + 1 <= N && board[R + 1][C] == 0)
				{
					board[R + 1][C] = i;
					new_q.push({ R + 1, C });
				}

				//left
				if (1 <= C - 1 && board[R][C - 1] == 0)
				{
					board[R][C - 1] = i;
					new_q.push({ R, C - 1 });
				}

				//right
				if (C + 1 <= N && board[R][C + 1] == 0)
				{
					board[R][C + 1] = i;
					new_q.push({ R, C + 1 });
				}
			}
			//새로 쌓인 좌표들을 등록
			qs[i].swap(new_q);
		}
	}

	cout << board[X][Y];
}