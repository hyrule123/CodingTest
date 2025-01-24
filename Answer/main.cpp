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
백준 28291 (레드스톤) [그래프]
*/

#include <string>
#include <queue>
#include <vector>
int w, h;

struct coord 
{ 
	int x, y;
	coord operator +(const coord& o) const 
	{
		return { x + o.x, y + o.y };
	}
	bool is_valid() const
	{
		return !(x < 0 || w <= x || y < 0 || h <= y);
	}
};
constexpr coord dirs[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
constexpr string_view block_str = "redstone_block", lamp_str = "redstone_lamp", dust_str = "redstone_dust";

using pci = pair<coord, int>;
#define cod first
#define energy second
queue<pci> bfs;
vector<coord> lamp_pos;
int board[50][50];

void solve()
{
	cin >> w >> h;

	//기본 16으로 초기화
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			board[i][j] = 16;
		}
	}

	int n; cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string input; coord c;
		cin >> input >> c.x >> c.y;
	
		if (input == block_str)
		{
			bfs.push({ c, 15 });
			board[c.x][c.y] = 0;
		}
		else if (input == lamp_str)
		{
			lamp_pos.push_back(c);
		}
		else if (input == dust_str)
		{
			board[c.x][c.y] = 0;
		}
	}

	while (false == bfs.empty())
	{
		pci p = bfs.front(); bfs.pop();
		board[p.cod.x][p.cod.y] = p.energy;

		if (p.energy <= 0) { continue; }

		for (int i = 0; i < 4; ++i)
		{
			coord next_c = p.cod + dirs[i];
			if (false == next_c.is_valid()) { continue; }
			//레드스톤 블록이 아닐 경우 or 이미 같거나 큰 에너지로 갱신이 된 블록인 경우
			if (p.energy - 1 <= board[next_c.x][next_c.y]) { continue; }
			bfs.push({ next_c, p.energy - 1 });
		}
	}

	//사방을 확인해서 동력이 연결된 부분이 있는지 확인
	//단 하나라도 연결되어있지 않을 경우 fail
	for (const auto& lamp : lamp_pos)
	{
		bool cur_on = false;
		for (int i = 0; i < 4; ++i)
		{
			coord roundpos = lamp + dirs[i];
			if (roundpos.is_valid())
			{
				cur_on |= (0 < board[roundpos.x][roundpos.y] && board[roundpos.x][roundpos.y] < 16);
			}
		}
		if (false == cur_on)
		{
			cout << "failed";
			return;
		}
	}

	cout << "success";
}