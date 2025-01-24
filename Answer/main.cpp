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
백준 32102 (삼색정리) [수학?]
참고 사이트: https://blog.naver.com/jinhan814/223535076654
중요한 조건: R_left + G_left + B_left = N * M
많은 순서대로 a, b, c (== a <= b <= c)라고 할 경우
c가 최소가 되는 a + b + c = NM은 a = b = c일 때이다
3c = NM -> "c >= ceil(NM / 3)"


1. 가장 많이 칠해야 하는 색이 전체 칸 수의 반(소수점은 올림)을 초과할 경우, 정답은 존재하지 않음.
	ex. 9칸을 칠해야 한다면 R은 5를 넘어가면 안 된다.
	체스판을 생각해보자
	R x R
	x R x
	R x R
	-> c <= ceil(NM / 2)

2. 가장 많이 칠해야 하는 색을 좌측 상단부터 칠해준다.
	색이 더 많이 칠해질 수 있는 부분을 '검은색' 부분이라고 할 때(홀수 * 홀수 체스판을 생각해보자)
	검은색 부분은 ceil(NM / 2), 흰색 부분은 floor(NM / 2)
	검은 c개 칠했으니까 ceil(NM / 2) - c가 남아있다.
	a + b로 칠해야 하는 영역은 floor(NM / 2) + ceil(NM / 2) - c
	만약 b가 칠해야 하는 floor(NM / 2) + ceil(NM / 2) - c 부분이
	ceil(NM / 2)를 넘어선다면, 즉 ceil(NM / 2) < b 가 된다면
	아까 분명히 확인했던 ceil(NM / 2) <= c와 모순되는 상황이 발생하게 된다.(존재할 수 없는 상황)
	그러므로 c + a개로 모든 검은 영역을 커버할 수 있다.

	c + a개로 검은 영역을 칠해주고, a영역쪽에는 b를 넣어서 중복되지 않게 한 다음
	남은 a를 c로 둘러쌓인 영역에 칠해준다
	c a c
	b c b
	c b c

3. 코너 케이스
	c가 최소값이 되는 경우, 즉 a = b = c가 되는 경우 위의 알고리즘으로 칸을 채울 수 없는 경우가 발생한다.
	c a c
	b a b
	하지만 이때는 세가지 수를 (i + j) % mod로 차례대로 하나씩 배치해주면 겹치지 않게 배치가 가능하다.

* 요약
* 아예 칠할수 없는 상황을 확인
* 가장 많이 칠할수 있는 색으로 검은색 부분을 색칠, 다 못칠하면 가장 적은 색으로 색칠
* 뒤에서부터 가장 적은색, 중간 색으로 적절히 배치하면 배치가 가능
*/
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
constexpr int R = 0, G = 1, B = 2;
struct pair_color
{
	int count;
	char color;

	auto operator <=>(const pair_color& o) const
	{
		return count <=> o.count;
	}
};
int n_row, n_col;
array<pair_color, 3> rgb_left = { { {0, 'R'}, {0, 'G'}, {0, 'B'} } };
vector<vector<char>> board;

void solve()
{
	cin >> n_row >> n_col
		>> rgb_left[R].count >> rgb_left[G].count >> rgb_left[B].count;

	sort(rgb_left.begin(), rgb_left.end());

	int threshold = (int)ceil((double)(n_row * n_col) / 2.0);

	//판의 반을 초과하여 가장 많은 c 색으로 칠해야 하는 경우는 칠하기가 불가능
	if (threshold < rgb_left.back().count)
	{
		cout << "NO";
		return;
	}

	board.resize(n_row, vector<char>(n_col + 1));

	//갯수가 모두 같다면
	if (rgb_left[0].count == rgb_left[1].count && rgb_left[1].count == rgb_left[2].count)
	{
		for (int r = 0; r < n_row; ++r)
		{
			for (int c = 0; c < n_col; ++c)
			{
				//n_row 또는 n_col 중 하나가 3의 배수임을 활용
				board[r][c] = rgb_left[(r + c) % 3].color;
			}
		}
	}
	else
	{
		//가장 많은 색을 일단 많이 칠할수 있는 부분에 칠하고,
		//가장 많은 색을 다 썼으면 가장 적은 색으로 나머지 부분을 칠한다
		for (int r = 0; r < n_row; ++r)
		{
			for (int c = r % 2; c < n_col; c += 2)
			{
				if (0 < rgb_left[2].count)
				{
					board[r][c] = rgb_left[2].color;
					rgb_left[2].count--;
				}
				else
				{
					board[r][c] = rgb_left[0].color;
				}
			}
		}

		for (int r = n_row - 1; r >= 0; --r)
		{
			for (int c = n_col - 1; c >= 0; --c)
			{
				if (board[r][c] == 0)
				{
					/*
					* 예외처리: 밑 행이 rgb_left[0]일 경우: 아래와 같은 상황
					R ? R
					  B
					? 자리에 B를 넣으면 큰일난다!!
					*/
					//가장 먼저 체크
					if (r + 1 < n_row && board[r + 1][c] == rgb_left[0].color)
					{
						board[r][c] = rgb_left[1].color;
						rgb_left[1].count--;
					}
				}
			}
		}

		for (int r = n_row - 1; r >= 0; --r)
		{
			for (int c = n_col - 1; c >= 0; --c)
			{
				if (board[r][c] == 0)
				{
					if (0 < rgb_left[1].count)
					{
						board[r][c] = rgb_left[1].color;
						rgb_left[1].count--;
					}
					else
					{
						board[r][c] = rgb_left[0].color;
					}
				}
			}
		}
	}

	cout << "YES" << '\n';
	for (int r = 0; r < n_row; ++r)
	{
		cout << board[r].data() << '\n';
	}
}