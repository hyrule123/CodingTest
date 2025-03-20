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
백준 14225 (부분수열의 합) [조합]
*/
#include <bitset>
#include <vector>
#include <algorithm>
int seq[20], N;
bitset<2'000'001> is_number;

void solve()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> seq[i];
	}

	for (int len = 1; len <= N; ++len)
	{
		vector<bool> comb; comb.resize(N);
		for (int i = N - len; i < N; ++i)
		{
			comb[i] = true;
		}

		do
		{
			int sum = 0;
			for (int i = 0; i < N; ++i)
			{
				if (comb[i])
				{
					sum += seq[i];
				}
			}
			is_number[sum] = true;
		} while (next_permutation(comb.begin(), comb.end()));
	}

	for (int i = 1; i < N * 100'000; ++i)
	{
		if (is_number[i]) { continue; }

		cout << i;
		return;
	}
}