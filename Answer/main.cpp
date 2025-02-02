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
백준 16929 (Two Dots) [그래프]
*/
#include <vector>
#include <string>
#include <queue>
int N, M;
vector<string> board;
struct coord
{
	int r, c;
	coord operator +(const coord& o)
	{
		return { r + o.r, c + o.c };
	}
	bool is_valid()
	{
		return !(r < 0 || N <= r || c < 0 || M <= c);
	}
	int to_1d()
	{
		return r * M + c;
	}
};
constexpr coord dirs[] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
vector<vector<int>> graph;
vector<bool> visited;

void make_graph()
{
	graph.resize(M * N);
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			coord cur = { r,c };
			for (const auto& dir : dirs)
			{
				coord child = cur + dir;
				if (false == child.is_valid())
				{
					continue;
				}

				//색이 같으면 간선을 연결
				if (board[r][c] == board[child.r][child.c])
				{
					graph[cur.to_1d()].push_back(child.to_1d());
				}
			}
		}
	}
}

bool detect_cycle(int start)
{
	struct travel
	{
		int now, from;
	};
	queue<travel> q;
	
	visited[start] = true;
	q.push({ start, -1 });

	while (false == q.empty())
	{
		travel cur = q.front(); q.pop();
		for (int next : graph[cur.now])
		{
			if (next == cur.from) { continue; }

			if (visited[next]) { return true; }

			visited[next] = true;
			q.push({ next, cur.now });
		}
	}

	return false;
}

void solve()
{
	cin >> N >> M;
	board.resize(N, string((size_t)M, 0));
	for (int i = 0; i < N; ++i)
	{;
		cin >> board[i];
	}
	
	make_graph();

	visited.resize(graph.size());
	for (int i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == false)
		{
			if (detect_cycle(i))
			{
				cout << "Yes";
				return;
			}
		}
	}

	cout << "No";
}