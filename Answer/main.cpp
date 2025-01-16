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
백준 25605 (입맛이 까다로운 코알라가 유칼립투스 잎을 행복하게 먹을 수 있는 방법) [DP][코드 분석]
<https://www.acmicpc.net/source/64394769> 소스코드 분석
dp[i][j][k]: i: prev, cur / j: 현재 날짜 / k: 독성 수치 일 때 얻는 행복도의 최대값
최대 1000개의 잎에 대해 전체를 저장하지 않고
prev, cur 두가지 상태만 저장함으로써 메모리를 절약한 것 같음.
dp[i & 1]: 현재 잎
dp[(i + 1) & 1]: 이전 잎
*/
int dp[2][105][105];

void solve() 
{
	int n, m; cin >> n >> m;
	int mx, rem, c; cin >> mx >> rem >> c;
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= mx; j++)
		{
			dp[0][i][j] = -(1 << 29);
		}
	}
			
	dp[0][0][c] = 0;
	for (int j = 1; j <= mx; j++) 
	{
		for (int k = 0; k <= mx; k++)
		{
			dp[0][j][max(0, k - rem)] = max(dp[0][j][max(0, k - rem)], dp[0][j - 1][k]);
		}       
	}
	for (int i = 1; i <= n; i++) 
	{
		int x, y; cin >> x >> y;
		for (int k = 0; k <= m; k++)
		{
			for (int j = 0; j <= mx; j++)
			{
				dp[i & 1][k][j] = dp[(i + 1) & 1][k][j];
			}
		}

		for (int j = 1; j <= m; j++) 
		{
			for (int k = 0; k <= mx - x; k++) 
			{
				//max(현재, (이전 잎의 어제 값))
				auto& cur = dp[i & 1][j][max(0, k + x - rem)];
				cur = max(
					cur, 
					dp[(i + 1) & 1][j - 1][k] + y					
				);
			}
			for (int k = 0; k <= mx; k++)
			{
				//잎을 먹지 않음, 어제
				auto& cur = dp[i & 1][j][max(0, k - rem)];
				cur = max(cur, dp[i & 1][j - 1][k]);
			}
		}
	}
	int ans = -1;
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= mx; j++)
		{
			ans = max(dp[n & 1][i][j], ans);
		}
	}

	cout << ans;
}