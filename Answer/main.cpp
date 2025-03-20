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
백준 14225 (부분수열의 합) [조합][v2]
참고: https://cocoon1787.tistory.com/333
재귀를 통한 조합 구현(더하냐 안더하냐)
*/
#include <bitset>
#include <vector>
#include <algorithm>
#include <stack>
int seq[20], N;
bitset<2'000'001> is_number;
stack<pair<int, int>> stk;

void solve()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> seq[i];
	}

	stk.push({ 0, 0 });
	while (false == stk.empty())
	{
		auto [cur_idx, sum] = stk.top(); stk.pop();
		is_number[sum] = true;

		if (cur_idx < N)
		{
			//더하지 않거나
			stk.push({ cur_idx + 1 , sum });

			//더하거나
			stk.push({ cur_idx + 1, sum + seq[cur_idx] });
		}
	}

	for (int i = 1; i < N * 100'000; ++i)
	{
		if (is_number[i]) { continue; }

		cout << i;
		return;
	}
}