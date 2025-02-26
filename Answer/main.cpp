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
백준 11052(카드 구매하기) [DP]
카드 N장을 최대한 비싸게 구매해야 한다
현재 카드팩 Pi와 임의의 카드팩 Pa + Pb를 더해서 i장을 모으는 방법을 계산
*/
int N, dp[1001];

void solve()
{
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		cin >> dp[i];

		for (int j = 1; j <= i - 1; ++j)
		{
			dp[i] = max(dp[i], dp[i - j] + dp[j]);
		}
	}

	cout << dp[N];
}