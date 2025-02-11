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
백준 11965 (Bessie's Dream) [BFS][다익스트라]
*/
#include <vector>
#include <queue>
vector<vector<int>> maze;

struct block_info
{
	int dist;
	bool orange_passed;
};
vector<vector<block_info>> visited;
enum colors { red, pink, orange, blue, purple };

int size_r, size_c;
struct coord
{
	int r, c;
	coord operator + (const coord& cd) const
	{
		return { r + cd.r, c + cd.c };
	}
	coord operator * (int i) const
	{
		return { r * i, c * i };
	}
	coord operator -() const
	{
		return { -r, -c };
	}

	bool operator == (const coord& cd) const
	{
		return (r == cd.r && c == cd.c);
	}

	bool is_valid()
	{
		return !(r < 0 || size_r <= r || c < 0 || size_c <= c);
	}
};
constexpr coord dirs[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

//first: dist, second: passed purple block
int passthrough(const coord& cur, const coord& dir)
{
	int ret = 0;

	coord now = cur;
	while (true)
	{
		coord temp = now + dir;
		if (temp.is_valid())
		{
			if (maze[temp.r][temp.c] == purple)
			{
				now = temp;
				++ret;
				continue;
			}
			else
			{
				break;
			}
		}
		else { break; }
	}

	return ret;
}

struct travel
{
	coord cod;
	int dist;
	bool is_orange_smell;

	auto operator <=> (const travel& o) const
	{
		return dist <=> o.dist;
	}
};
priority_queue<travel, vector<travel>, greater<>> q;

int BFS()
{
	travel from{};
	from.cod = { 0, 0 };
	from.dist = 0;
	from.is_orange_smell = false;
	visited[0][0].dist = 1;
	q.push(from);

	while (false == q.empty())
	{
		from = q.top(); q.pop();

		for (const auto& dir : dirs)
		{
			travel to{};
			int result = passthrough(from.cod, dir);
			//보라색 블록을 한 칸이라도 지나왔을 경우
			if (0 < result)
			{
				to.cod = from.cod + dir * result;
				to.dist = from.dist + result;
				to.is_orange_smell = false;

				//한칸 더 가본다
				coord next = to.cod + dir;
				//다음칸 갈수 있고 + 핑크색이고
				if (next.is_valid() && maze[next.r][next.c] == pink)
				{
					//아직 방문하지 않았다면 방문(방문했다면 더이상 방문 X)
					if (visited[next.r][next.c].dist == 0)
					{
						to.cod = next;
						to.dist++;
						visited[to.cod.r][to.cod.c].dist = to.dist;
						if (to.cod.r + 1 == size_r && to.cod.c + 1 == size_c)
						{
							return to.dist;
						}
						q.push(to);
					}
				}
				//다음칸에 갈 수 없을 경우 이번 보라색 칸 방문 여부 확인 후 방문
				else if (visited[to.cod.r][to.cod.c].dist == 0)
				{
					visited[to.cod.r][to.cod.c].dist = to.dist;
					if (to.cod.r + 1 == size_r && to.cod.c + 1 == size_c)
					{
						return to.dist;
					}
					q.push(to);
				}
			}
			//보라색이나 핑크색 블록이 아닐 경우
			//빨간색, 주황색, 파란색
			else
			{
				to.cod = from.cod + dir;
				if (to.cod.is_valid())
				{
					int color = maze[to.cod.r][to.cod.c];
					switch (color)
					{
					case red:
						continue;
					case pink:
						to.is_orange_smell = from.is_orange_smell;
						to.dist = from.dist + 1;
						break;
					case orange:
						to.is_orange_smell = true;
						to.dist = from.dist + 1;
						break;
					case blue:
						if (false == from.is_orange_smell)
						{
							continue;
						}

						to.is_orange_smell = from.is_orange_smell;
						to.dist = from.dist + 1;
						break;
					default:
						continue;
					}

					if (visited[to.cod.r][to.cod.c].dist == 0)
					{
						visited[to.cod.r][to.cod.c].dist = to.dist;
						visited[to.cod.r][to.cod.c].orange_passed = to.is_orange_smell;

						if (to.cod.r + 1 == size_r && to.cod.c + 1 == size_c)
						{
							return to.dist;
						}

						q.push(to);
					}
					else if (to.is_orange_smell && false == visited[to.cod.r][to.cod.c].orange_passed)
					{
						visited[to.cod.r][to.cod.c].dist = to.dist;
						visited[to.cod.r][to.cod.c].orange_passed = to.is_orange_smell;

						if (to.cod.r + 1 == size_r && to.cod.c + 1 == size_c)
						{
							return to.dist;
						}

						q.push(to);
					}
				}
			}
		}

	}

	return -1;
}

void solve()
{
	cin >> size_r >> size_c;
	maze.resize(size_r, vector<int>((size_t)size_c));
	visited.resize(size_r, vector<block_info>((size_t)size_c));

	for (int r = 0; r < size_r; ++r)
	{
		for (int c = 0; c < size_c; ++c)
		{
			cin >> maze[r][c];
		}
	}

	cout << BFS();
}