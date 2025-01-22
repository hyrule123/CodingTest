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

	그러므로 a가 오링나는 상황은 걱정 안해도 되고 c < ceil(NM / 2)만 만족하면 일단 그릴 수 있다는 소리이다
*/
#include <cmath>
#include <vector>
#include <algorithm>
constexpr int R = 0, G = 1, B = 2;
#define count first
#define color second
int n_row, n_col;
vector<pair<int, char>> rgb_left = { {0, 'R'}, {0, 'G'}, {0, 'B'} };
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
		//가장 많은 색을 일단 많이 칠할수 있는 부분에 칠함
		for (int r = 0; r < n_row; ++r)
		{
			bool stop = false;
			for (int c = r % 2; c < n_col; c += 2)
			{
				if (rgb_left[2].count--)
				{
					board[r][c] = rgb_left[2].color;
				}
				else
				{
					stop = true;
					break;
				}
			}
			if (stop) break;
		}

		//반대쪽에서 돌아오면서 빈 공간에 나머지 색을 번갈아가며 칠한다
		bool toggle = 0;
		for (int r = n_row - 1; r >= 0; --r)
		{
			for (int c = n_col - 1; c >= 0; --c)
			{
				if (board[r][c] == 0)
				{
					//위쪽에서 내려오는 것이므로 중복 검사는 아래쪽만 해주면 됨
					//또는 한 쪽을 다 썼을 경우
					bool is_down_same = r + 1 < n_row && board[r + 1][c] == rgb_left[toggle].color;
					if (is_down_same || rgb_left[toggle].count == 0)
					{
						toggle = !toggle;
					}
					
					board[r][c] = rgb_left[toggle].color;
					rgb_left[toggle].count--;
					toggle = !toggle;
				}
			}
		}
	}

	for (int r = 0; r < n_row; ++ r)
	{
		cout << board[r].data() << '\n';
	}
}