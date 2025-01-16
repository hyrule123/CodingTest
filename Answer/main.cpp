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
백준 25605 (입맛이 까다로운 코알라가 유칼립투스 잎을 행복하게 먹을 수 있는 방법) [DP]
유칼립투스를 먹거나 안먹거나 -> DP
독성 = 무게
행복도 = 가치
*/
//DP[d][l][p]: i번째 날, j번째 유칼립투스 잎, 현재 축적된 독성 p

using pii = pair<int, int>;
#define poison first
#define happiness second
int leaf_limit, day_limit, poison_limit, daily_depoison, start_poison, dp[101][1001][101];
pii leaves[1001];

void solve() 
{
	cin >> leaf_limit >> day_limit >> poison_limit >> daily_depoison >> start_poison;
	for (int i = 1; i <= leaf_limit; ++i) 
	{
		cin >> leaves[i].poison >> leaves[i].happiness;
	}
	
	//현재 날
	for (int d = 1; d <= day_limit; ++d)
	{
		//일일 해독량이 반영된 현재 중독수치
		int cur_poison = max(0, start_poison - (daily_depoison * (d - 1)));

		//현재 놓인 잎 번호
		for (int l = 1; l <= leaf_limit; ++l)
		{
			//이번에 잎 l을 처음으로 먹는 경우: 먹고 바로 잔다
			
			int eat_after = cur_poison + leaves[l].poison;
			if (eat_after <= poison_limit)
			{
				eat_after = max(0, eat_after - daily_depoison);
				dp[d][l][eat_after] = leaves[l].happiness;
			}
			
			for (int p = 0; p <= poison_limit; ++p)
			{
				//그대로 두고 자고 일어남
				int sleep_after = max(0, p - daily_depoison);
				dp[d][l][sleep_after] = max(dp[d][l][sleep_after], dp[d - 1][l][p]);

				//이번 잎을 거름
				dp[d][l][p] = max(dp[d][l][p], dp[d][l - 1][p]);

				//이번 잎을 먹음(처음으로 먹는 잎이 아닐 경우): 먹고 바로 취침
				int eat_after = max(0, p + leaves[l].poison);
				if (eat_after <= poison_limit && dp[d - 1][l - 1][p] != 0)
				{
					eat_after = max(0, eat_after - daily_depoison);
					dp[d][l][eat_after] = max(dp[d][l][eat_after], dp[d - 1][l - 1][p] + leaves[l].happiness);
				}
			}
		}
	}

	int ans = 0;
	for (int p = 0; p <= poison_limit; ++p)
	{
		ans = max(ans, dp[day_limit][leaf_limit][p]);
	}
	cout << ans;
}