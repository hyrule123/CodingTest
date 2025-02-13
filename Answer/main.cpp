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
백준 26598 (색종이와 공예) [BFS]

* 직사각형이 아닐 때만 놀려주면 되니까
* 새로운 문자 발견 시 -> 가로(col)로 쭉 확인 후 세로로 이어서 확인하면 되지 않을까?
* 그냥 시키는대로 할걸 최적화를 너무 생각한 듯
*/

#include <stack>

int r_size, c_size;
char inputs[1001][1001];

bool check(int r_start, int c_start)
{
	const char cur_char = inputs[r_start][c_start];
	inputs[r_start][c_start] = 0;

	pair<int, int> left_top{ 11111, 11111 }, right_bottom{};
	stack<pair<int, int>> q;
	int char_count = 0;
	q.push({ r_start, c_start });
	while (false == q.empty())
	{
		pair<int, int> cur = q.top(); q.pop();
		++char_count;

		left_top.first = min(left_top.first, cur.first);
		left_top.second = min(left_top.second, cur.second);
		right_bottom.first = max(right_bottom.first, cur.first);
		right_bottom.second = max(right_bottom.second, cur.second);

		if (0 <= cur.first - 1 && inputs[cur.first - 1][cur.second] == cur_char)
		{
			inputs[cur.first - 1][cur.second] = 0;
			q.push({ cur.first - 1, cur.second });
		}
		if (r_size > cur.first + 1 && inputs[cur.first + 1][cur.second] == cur_char)
		{
			inputs[cur.first + 1][cur.second] = 0;
			q.push({ cur.first + 1, cur.second });
		}
		if (0 <= cur.second - 1 && inputs[cur.first][cur.second - 1] == cur_char)
		{
			inputs[cur.first][cur.second - 1] = 0;
			q.push({ cur.first, cur.second - 1 });
		}
		if (c_size > cur.second + 1 && inputs[cur.first][cur.second + 1] == cur_char)
		{
			inputs[cur.first][cur.second + 1] = 0;
			q.push({ cur.first, cur.second + 1 });
		}
	}

	int size = (right_bottom.first - left_top.first + 1) * (right_bottom.second - left_top.second + 1);
	if (char_count == size) { return true; }

	return false;
}

void solve()
{
	cin >> r_size >> c_size;

	for (int r = 0; r < r_size; ++r)
	{
		cin >> inputs[r];
	}

	for (int r = 0; r < r_size; ++r)
	{
		for (int c = 0; c < c_size; ++c)
		{
			if (inputs[r][c] != 0)
			{
				if (false == check(r, c))
				{
					cout << "BaboBabo";
					return;
				}
			}
		}
	}


	cout << "dd";
}
