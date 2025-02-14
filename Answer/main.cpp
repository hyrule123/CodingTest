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
백준 2092 (집합의 개수) [DP]
dp[i][j]: i 이하의 숫자 j개를 썼을 때 만들 수 있는 조합의 개수
*/
#include <vector>
constexpr int mod = 1'000'000;
int number_max, total_count, min_K, max_K;
int numbers_count[201], dp[201][4001];

void solve()
{
	cin >> number_max >> total_count >> min_K >> max_K;
	for (int i = 0; i < total_count; ++i)
	{
		int input; cin >> input;
		numbers_count[input]++;
	}

	dp[0][0] = 1;
	for (int n = 1; n <= number_max; ++n)
	{
		//아무것도 안 뽑은 집합(공집합)도 1개로 친다
		dp[n][0] = 1;
		for (int c = 1; c <= numbers_count[n]; ++c)
		{
			//숫자 n을 c개 써서 만들 수 있는 조합 1개씩 추가
			//1 3개 있으면 1, 11, 111
			dp[n][c] = 1;
		}

		for (int a = 1; a <= total_count; ++a)
		{
			//n을 쓰지 않는 조합의 개수를 추가
			dp[n][a] = (dp[n][a] + dp[n - 1][a]) % mod;

			for (int b = 1; b <= numbers_count[n]; ++b)
			{
				if (a - b >= 1)
				{
					//a - b개에 b, b, ..., b, b를 붙이는 방법의 수를 더한다
					dp[n][a] = (dp[n][a] + dp[n - 1][a - b]) % mod;
				}
				else
				{
					break;
				}
			}
		}
	}

	int ans = 0;
	for (int k = min_K; k <= max_K; ++k)
	{
		ans = (ans + dp[number_max][k]) % mod;
	}

	cout << ans;
}
