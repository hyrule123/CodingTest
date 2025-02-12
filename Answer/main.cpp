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
백준 26598 (색종이와 공예) [브루트 포스][오답]

* 직사각형이 아닐 때만 놀려주면 되니까
* 새로운 문자 발견 시 -> 가로(col)로 쭉 확인 후 세로로 이어서 확인하면 되지 않을까?
* 브루트포스로 하니까 시간초과 발생...
*/

#include <queue>
queue<pair<int, int>> job_q;
int r_size, c_size;
char inputs[1001][1001];

bool check(int r_start, int c_start)
{
	const char cur_char = inputs[r_start][c_start];

	//테두리(상하좌우) 확인
	int top_side = 0, left_side = 0, bottom_side = 0, right_side = 0;
	for (int r = r_start; r < r_size; ++r)
	{
		if (cur_char != inputs[r][c_start]) { break; }
		++left_side;
	}
	for (int c = c_start; c < c_size; ++c)
	{
		if (cur_char != inputs[r_start][c]) { break; }
		++top_side;
	}
	for (int r = r_start; r < r_size; ++r)
	{
		if (cur_char != inputs[r][c_start + top_side - 1]) { break; }
		++right_side;
	}
	for (int c = c_start; c < c_size; ++c)
	{
		if (cur_char != inputs[r_start + left_side - 1][c]) { break; }
		++bottom_side;
	}

	if (left_side != right_side || top_side != bottom_side)
	{
		return false;
	}

	//내부
	for (int r = r_start + 1; r < r_start + left_side - 1; ++r)
	{
		for (int c = c_start + 1; c < c_start + top_side - 1; ++c)
		{
			if (cur_char != inputs[r][c])
			{
				return false;
			}
		}
	}

	if (c_start + top_side < c_size)
	{
		job_q.push({ r_start, c_start + top_side });
	}
	if (r_start + left_side < r_size)
	{
		job_q.push({ r_start + left_side, c_start });
	}

	return true;
}

void solve()
{
	cin >> r_size >> c_size;
	
	for (int r = 0; r < r_size; ++r)
	{
		cin >> inputs[r];
	}

	job_q.push({ 0, 0 });

	while (false == job_q.empty())
	{
		auto coord = job_q.front(); job_q.pop();

		if (false == check(coord.first, coord.second))
		{
			cout << "BaboBabo";
			return;
		}
	}

	cout << "dd";
}
