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
백준 1398 (동전 문제) [그리디][오답]

동전이 배수 관계가 아니기 때문에 단순 그리디로 해결할 수 없다.
*/

#include <vector>
#include <algorithm>
using ull = unsigned long long;
vector<ull> inputs;
vector<ull> coins;

void solve()
{
	ull T; cin >> T;
	inputs.resize(T);
	ull MAX = 0;
	for (auto& input : inputs)
	{
		cin >> input;
		MAX = max(MAX, input);
	}
	
	for (ull num = 1;; num *= 10)
	{
		if (num > MAX) { break; }
		coins.push_back(num);
	}
	for (ull num = 25;; num *= 100)
	{
		if (num > MAX) { break; }
		coins.push_back(1 * num);
	}

	sort(coins.begin(), coins.end());

	for (auto input : inputs)
	{
		ull count = 0;
		for (ull i = coins.size() - 1; i != -1; --i)
		{
			while (true)
			{
				if (coins[i] <= input)
				{
					input -= coins[i];
					++count;
				}
				else
				{
					break;
				}
			}
		}
		cout << count << '\n';
	}
}