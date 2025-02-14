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
백준 17829 (222-풀링) [재귀]
아이디어
ㅁㅁ -> ㅁ
ㅁㅁ 
같은 공간을 재사용해도 값을 구하는데 문제가 발생하지 않으므로
같은 공간 안에서 크기를 계속 줄여 나간다
*/
#include <vector>
#include <array>
#include <algorithm>
struct _2by2mat
{
	array<int, 4> m;

	//insertion sort
	int get_second()
	{
		for (int i = 1; i < 4; ++i)
		{
			int cur = m[i], check = i - 1;
			while (check >= 0 && m[check] > cur)
			{
				m[check + 1] = m[check];
				--check;
			}
			m[check + 1] = cur;
		}

		return m[2];
	}
};

int N;
vector<_2by2mat> mats;
int get_last_num(int prev_side)
{
	if (prev_side == 1)
	{
		return mats[0].get_second();
	}

	int new_side = prev_side / 2;
	for (int r = 0; r < new_side; ++r)
	{
		for (int c = 0; c < new_side; ++c)
		{
			_2by2mat& cur_mat = mats[r * new_side + c];

			int prev_r = r * 2, prev_c = c * 2;
			cur_mat.m[0] = mats[prev_r * prev_side + prev_c].get_second();
			cur_mat.m[1] = mats[prev_r * prev_side + (prev_c + 1)].get_second();
			cur_mat.m[2] = mats[(prev_r + 1) * prev_side + prev_c].get_second();
			cur_mat.m[3] = mats[(prev_r + 1) * prev_side + (prev_c + 1)].get_second();
		}
	}

	return get_last_num(new_side);
}

void solve()
{
	cin >> N;
	mats.resize(N * N / 4);

	int board_size = N / 2, r = 0;
	for (int r = 0; r < board_size; ++r)
	{
		for (int c = 0; c < board_size; ++c)
		{
			auto& cur_mat = mats[r * board_size + c];
			cin >> cur_mat.m[0] >> cur_mat.m[1];
		}		
		for (int c = 0; c < board_size; ++c)
		{
			auto& cur_mat = mats[r * board_size + c];
			cin >> cur_mat.m[2] >> cur_mat.m[3];
		}
	}

	cout << get_last_num(board_size);
}