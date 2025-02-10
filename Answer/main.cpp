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
백준 11965 (Bessie's Dream) [BFS][오답-메모리 초과]
visited를 안 썼다...
*/
#include <vector>
#include <queue>
vector<vector<int>> maze;
enum colors { red, pink, orange, blue, purple };

int size_r, size_c;
struct coord
{
	int r, c;
	coord operator + (const coord& cd) const
	{
		return { r + cd.r, c + cd.c };
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

struct travel
{
	coord cod, dir;
	int dist;
	bool is_orange_smell;
};

bool check(const travel& from, travel& to, const coord& dir)
{
	if (false == to.cod.is_valid()) { return false; }

	switch (maze[to.cod.r][to.cod.c])
	{
	case red:
		return false;
	case pink:
		to.dist = from.dist + 1;
		to.dir = dir;
		to.is_orange_smell = from.is_orange_smell;
		return true;
	case orange:
		to.dist = from.dist + 1;
		to.dir = dir;
		to.is_orange_smell = true;
		return true;
	case blue:
		if (false == from.is_orange_smell)
		{
			return false;
		}

		to.dist = from.dist + 1;
		to.dir = dir;
		to.is_orange_smell = from.is_orange_smell;
		return true;
	case purple:
		to.dist = from.dist + 1;
		to.dir = dir;
		to.is_orange_smell = false;
		return true;
	default:
		break;
	}

	return false;
}

int BFS()
{
	queue<travel> q;
	travel from{};
	from.cod = { 0, 0 };
	from.dir = { -1, -1 };
	from.dist = 0;
	from.is_orange_smell = false;
	q.push(from);

	while (false == q.empty())
	{
		from = q.front(); q.pop();

		if (from.cod.r + 1 == size_r && from.cod.c + 1 == size_c)
		{
			return from.dist;
		}

		//제외할 좌표
		coord exclude{};
		travel dest{};

		//보라색 타일에서 진입한 경우를 가장 먼저 확인
		if (maze[from.cod.r][from.cod.c] == purple)
		{	
			//이동중이던 방향으로 가장 먼저 이동 가능한지 확인
			dest.cod = from.cod + from.dir;
			if (check(from, dest, from.dir))
			{
				//이동 가능할 경우 여기만 큐에 추가하고 다음 사이클로 넘어간다
				q.push(dest);
				continue;
			}
			else//해당 방향으로 이동 불가능할 경우
			{
				//제외할 좌표 등록. 여기 제외하고 나머지 길에 대해 확인한다.
				exclude = from.dir;
			}
		}

		for (const auto& dir : dirs)
		{
			//제외한 방향일 경우 continue
			if (exclude == dir) { continue; }

			//왔던 방향으로 돌아가는 경우 continue
			if (-dir == from.dir) { continue; }

			dest.cod = from.cod + dir;

			//이동 가능한 타일일 경우 이동
			if (check(from, dest, dir))
			{
				q.push(dest);
			}
		}
	}

	return -1;
}

void solve()
{
	cin >> size_r >> size_c;
	maze.resize(size_r, vector<int>((size_t)size_c));

	for (int r = 0; r < size_r; ++r)
	{
		for (int c = 0; c < size_c; ++ c)
		{
			cin >> maze[r][c];
		}
	}
	cout << BFS();
}