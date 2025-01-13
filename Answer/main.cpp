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
백준 25605 (입맛이 까다로운 코알라가 유칼립투스 잎을 행복하게 먹을 수 있는 방법) [오답(시간초과)][DP]
유칼립투스를 먹거나 안먹거나 -> DP
독성 = 무게
행복도 = 가치
*/
//DP[i][j]: i번쨰 날, 현재 독성 j, 값은 현재 행복도
using pii = pair<int, int>;
#define poison first
#define happiness second
int leaf_limit, day_limit, poison_limit, daily_depoison, start_poison, dp[101][101];
pii leaves[1001];

void rcsv(int cur_day, int prev_day, int prev_poison, int cur_leaf)
{
	//날짜 초과 시 중단
	if (day_limit < cur_day) { return; }
	
	//날짜가 지났을 경우 일정량만큼 해독된다
	int cur_poison = prev_poison;
	if (cur_day != prev_day)
	{
		cur_poison -= daily_depoison;
		if (cur_poison < 0) { cur_poison = 0; }
	}

	//먹을수 있을 경우 먹거나
	int poison_eat = cur_poison + leaves[cur_leaf].poison;
	if (poison_eat <= poison_limit)
	{
		dp[cur_day][poison_eat] = max(
			dp[cur_day][poison_eat],
			dp[cur_day - 1][prev_poison] + leaves[cur_leaf].happiness
		);
		rcsv(cur_day + 1, cur_day, poison_eat, cur_leaf + 1);
	}
	
	//일단 값을 그대로 전달
	dp[cur_day][cur_poison] =
		max(
			dp[cur_day][cur_poison],
			dp[cur_day - 1][prev_poison]
			);

	//다음 잎을 보거나
	if(cur_leaf < leaf_limit)
	{
		rcsv(cur_day, cur_day, cur_poison, cur_leaf + 1);
	}

	//잎을 두고 그냥 자거나
	rcsv(cur_day + 1, cur_day, cur_poison, cur_leaf);
}

void solve() {
	cin >> leaf_limit >> day_limit >> poison_limit >> daily_depoison >> start_poison;
	for (int i = 1; i <= leaf_limit; ++i) {
		cin >> leaves[i].poison >> leaves[i].happiness;
	}
	rcsv(1, 1, start_poison, 1);

	int ans = 0;
	for(int i = 0; i <= poison_limit; ++i)
	{
		ans = max(ans, dp[day_limit][i]);
	}
	cout << ans;
}