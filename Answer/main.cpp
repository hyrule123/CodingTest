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
백준 7453 (합이 0인 네 정수) [오답 - 시간 초과]
* map은 항상 정렬된 순서로 데이터를 저장한다는데 착안 + 투 포인터
* v2 만들어 보기: 투 포인터 말고 맵 검색을 사용해서 구현
*/
#include <map>
#include <cmath>

constexpr int a = 0, b = 1, c = 2, d = 3;
int n, abcd[4000][4];
map<int, int> ab, cd;

void solve()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> abcd[i][0] >> abcd[i][1] >> abcd[i][2] >> abcd[i][3];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			ab[abcd[i][a] + abcd[j][b]]++;
			cd[abcd[i][c] + abcd[j][d]]++;
		}
	}

	long long ans = 0;
	auto iter_ab = ab.begin();
	auto riter_cd = cd.rbegin();
	while (iter_ab != ab.end() && riter_cd != cd.rend())
	{
		int sum = iter_ab->first + riter_cd->first;
		//abs(ab) > abs(cd)
		if (sum < 0)
		{
			++iter_ab;
		}
		else if (sum > 0)
		{
			++riter_cd;
		}
		else //sum == 0
		{
			ans += (long long)iter_ab->second * (long long)riter_cd->second;
			++iter_ab;
			++riter_cd;
		}
	}
	
	cout << ans;
}