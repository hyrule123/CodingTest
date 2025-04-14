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
백준 12738 (가장 긴 증가하는 부분 수열 3) [dp][이진 탐색]
*/
#include <vector>
int N;
vector<int> input, dp;

int find_dp(int val)
{
	int start = 1, end = dp.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (dp[mid] == val)
		{
			return mid;
		}


		if (dp[mid] < val)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	return start;
}

void insert_dp(int val)
{
	if (dp.back() < val)
	{
		dp.push_back(val);
		return;
	}

	dp[find_dp(val)] = val;
}

void solve()
{
	cin >> N;
	input.resize(N + 1);
	for (int i = 1; i <= N; ++i)
	{
		cin >> input[i];
	}

	dp.reserve(N + 1);
	dp.push_back(std::numeric_limits<int>::min());
	for (int i = 1; i <= N; ++i)
	{
		insert_dp(input[i]);
	}

	cout << dp.size() - 1;
}