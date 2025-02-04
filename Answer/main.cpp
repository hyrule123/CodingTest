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
백준 12852 (1로 만들기 2) [복습][DP]
*/
#include <vector>
#include <cmath>
#include <stack>
constexpr int p1 = 1, div2 = 2, div3 = 3;
struct trail
{
	int min_count = 987'654'321, how;
};
vector<trail> dp;

void solve()
{
	int n; cin >> n;
	dp.resize(n + 1);

	dp[n].min_count = 0;
	for (int i = n - 1; 1 <= i; --i)
	{
		if (i * 3 <= n && dp[i * 3].min_count + 1 < dp[i].min_count)
		{
			dp[i].min_count = dp[i * 3].min_count + 1;
			dp[i].how = div3;
		}
		if (i * 2 <= n && dp[i * 2].min_count + 1 < dp[i].min_count)
		{
			dp[i].min_count = dp[i * 2].min_count + 1;
			dp[i].how = div2;
		}
		if (dp[i + 1].min_count + 1 < dp[i].min_count)
		{
			dp[i].min_count = dp[i + 1].min_count + 1;
			dp[i].how = p1;
		}
	}

	cout << dp[1].min_count << '\n';
	int backtrace = 1;
	stack<int> ans;
	
	while (backtrace < n)
	{
		ans.push(backtrace);

		if (dp[backtrace].how == div3)
		{
			backtrace *= 3;
		}
		else if (dp[backtrace].how == div2)
		{
			backtrace *= 2;
		}
		else//p1
		{
			backtrace += 1;
		}
	}
	ans.push(n);

	while (!ans.empty())
	{
		cout << ans.top() << ' ';
		ans.pop();
	}
}