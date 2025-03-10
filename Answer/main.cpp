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
백준 12761 (돌다리) [BFS]
*/
#include <queue>
queue<int> q;
constexpr int MAX = 100'001;
int A, B, N, M, moves[MAX];

inline bool push_n_check_end(int next, int cur)
{
	if (moves[next] != -1) { return false; }

	moves[next] = moves[cur] + 1;

	if (next == M) { 
		cout << moves[next];
		return true; 
	}

	q.push(next);
	return false;
}

void solve()
{
	memset(moves, 0xff, sizeof(moves));
	cin >> A >> B >> N >> M;
	
	if (N == M)
	{
		cout << 0;
		return;
	}

	q.push(N);
	moves[N] = 0;

	if (A < B)
	{
		swap(A, B);
	}

	while (false == q.empty())
	{
		int cur = q.front(); q.pop();
		
		if (cur * A < MAX && push_n_check_end(cur * A, cur)) { return; }
		if (cur * B < MAX && push_n_check_end(cur * B, cur)) { return; }

		if (0 <= cur - A && push_n_check_end(cur - A, cur)) { return; }
		if (cur + A < MAX && push_n_check_end(cur + A, cur)) { return; }

		if (0 <= cur - B && push_n_check_end(cur - B, cur)) { return; }
		if (cur + B < MAX && push_n_check_end(cur + B, cur)) { return; }

		if (0 <= cur - 1 && push_n_check_end(cur - 1, cur)) { return; }
		if (cur + 1 < MAX && push_n_check_end(cur + 1, cur)) { return; }
	}
}