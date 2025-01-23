#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
#include <random>
using namespace std;
bool solve();
int main() 
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	srand(time(0));

	int i = 10000;
	while (i--)
	{
		if (solve())
		{
			return 0;
		}
	}
	return 0;
}

/*
백준 32102 (삼색정리) [오답]
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
	-> c < ceil(NM / 2)


2. 가장 많이 칠해야 하는 색을 좌측 상단부터 칠해준다.
	색이 더 많이 칠해질 수 있는 부분을 '검은색' 부분이라고 할 때(홀수 * 홀수 체스판을 생각해보자)
	검은색 부분은 ceil(NM / 2)개가 있고
	이 부분을 c개 칠했으니까 ceil(NM / 2) - c가 남아있다.
	이제 이 부분을 나머지 두 색으로 채워주면 되는데,
	정방향으로 c를 칠했으므로
	역방향으로 b, a를 번갈아 칠해주면 될 것이다.
	근데 만약 ceil(NM / 2) - c를 칠하다 a가 오링 난다면?
	-> a < ceil(NM / 2) - c 가 될것이다.

	a = NM - (b + c) 이다.
	현재 a <= b <= c 라고 정의해 놓았으므로 b + c <= 2c는 자명하다
	-> a >= NM - 2c 라는 식을 유도할 수 있다.
	"NM - 2c <= a < ceil(NM / 2) - c" 라는 방정식이 성립해야 하는 것
	NM - 2c < ceil(NM / 2) - c
	NM - ceil(NM / 2) < c
	근데 c < ceil(NM / 2) 이므로
	NM - ceil(NM / 2) < c < ceil(NM / 2)
	NM - ceil(NM / 2) < ceil(NM / 2)
	NM < 0
	NM < 0 ? 이건 모순이 되므로 a < ceil(NM / 2) - c는 애초에 성립할수가 없다

	그러므로 a가 오링나는 상황은 걱정 안해도 되고 c < ceil(NM / 2)만 만족하면
	검은 부분에 c를 칠하고, 다 못칠한 부분은 a를 칠한 뒤 
	뒤에서부터 비어있는 부분에 b를 칠하다가 b를 다 쓰면 마지막에 a로 메꾸면 된다는 뜻
*/
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

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
vector<pair_color> rgb_left = { {0, 'R'}, {0, 'G'}, {0, 'B'} };
vector<vector<char>> board;

bool is_val_idx(int r, int c)
{
	return !(r < 0 || n_row <= r || c < 0 || n_col <= c);
}

void test()
{
	vector<string> vecs;
	string temp;
	while (cin >> temp)
	{
		vecs.push_back(temp);
	}

	for (size_t i = 0; i < vecs.size(); ++i)
	{
		for (size_t j = 0; j < vecs[i].size(); ++j)
		{
			if (is_val_idx(i - 1, j) && board[i - 1][j] == board[i][j])
			{
				for (int r = 0; r < n_row; ++r)
				{
					cout << board[r].data() << '\n';
				}
				assert(false);
			}
			if (is_val_idx(i + 1, j) && board[i + 1][j] == board[i][j])
			{
				for (int r = 0; r < n_row; ++r)
				{
					cout << board[r].data() << '\n';
				}
				assert(false);
			}
			if (is_val_idx(i, j - 1) && board[i][j - 1] == board[i][j])
			{
				for (int r = 0; r < n_row; ++r)
				{
					cout << board[r].data() << '\n';
				}
				assert(false);
			}
			if (is_val_idx(i, j + 1) && board[i][j + 1] == board[i][j])
			{
				for (int r = 0; r < n_row; ++r)
				{
					cout << board[r].data() << '\n';
				}
				assert(false);
			}
		}
	}
}

void print_data(int rr, int gg, int bb)
{
	cout << n_row << ' ' << n_col << ' ' << rr << ' ' << gg << ' ' << bb << '\n';
	for (int r = 0; r < n_row; ++r)
	{
		cout << board[r].data() << '\n';
	}
}

bool verify(int rr, int gg, int bb)
{
	int counts['R' + 1]{};
	for (int i = 0; i < n_row; ++i)
	{
		for (int j = 0; j < n_col; ++j)
		{
			if (is_val_idx(i - 1, j) && board[i - 1][j] == board[i][j])
			{
				print_data(rr, gg, bb);
				return true;
			}
			if (is_val_idx(i + 1, j) && board[i + 1][j] == board[i][j])
			{
				print_data(rr, gg, bb);
				return true;
			}
			if (is_val_idx(i, j - 1) && board[i][j - 1] == board[i][j])
			{
				print_data(rr, gg, bb);
				return true;
			}
			if (is_val_idx(i, j + 1) && board[i][j + 1] == board[i][j])
			{
				print_data(rr, gg, bb);
				return true;
			}

			counts[board[i][j]]++;
		}
	}

	if (rr != counts['R'])
	{
		print_data(rr, gg, bb);
		return true;
	}
	if (gg != counts['G'])
	{
		print_data(rr, gg, bb);
		return true;
	}
	if (bb != counts['B'])
	{
		print_data(rr, gg, bb);
		return true;
	}

	return false;
}

bool solve()
{
	//cin >> n_row >> n_col >> rgb_left[R].count >> rgb_left[G].count >> rgb_left[B].count;

	board.clear();
	n_row = rand() % 1999 + 2;
	n_col = rand() % 1999 + 2;
	int total, rr, gg, bb;
	do
	{
		total = n_row * n_col;
		rr = rgb_left[R].count = rand() % total;
		total -= rgb_left[R].count;
		gg = rgb_left[G].count = rand() % total;
		total -= rgb_left[G].count;
		bb = rgb_left[B].count = total;
	} while (0 < rr && 0 < gg && 0 < bb);
	rgb_left[R].color = 'R';
	rgb_left[G].color = 'G';
	rgb_left[B].color = 'B';

	sort(rgb_left.begin(), rgb_left.end());

	int threshold = (int)ceil((double)(n_row * n_col) / 2.0);

	//판의 반을 초과하여 가장 많은 c 색으로 칠해야 하는 경우는 칠하기가 불가능
	if (threshold < rgb_left.back().count)
	{
		//cout << "NO";
		return false;
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
					rgb_left[0].count--;
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
						rgb_left[0].count--;
					}
				}
			}
		}
	}

	return verify(rr, gg, bb);

	//cout << "YES" << '\n';
	for (int r = 0; r < n_row; ++ r)
	{
		cout << board[r].data() << '\n';
	}
}