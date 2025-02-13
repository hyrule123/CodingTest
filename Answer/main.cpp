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
백준 1398 (동전 문제) [DP][그리디]

동전이 배수 관계가 아니기 때문에 단순 그리디로 해결할 수 없다.
또한 10^15까지 액수가 나올 수 있으므로 단순 DP로는 메모리가 부족하다.
눈여겨볼 점은 화폐단위가 100단위로 끊어진다는 점
1, 10, 25
100, 1000, 2500(100 ~ 10000)
10'000, 100'000, 250'000 (10'000 ~ 1'000'000)

그러니까, 100단위로 끊어서 그 이상의 액수는 그 이상의 코인 3종으로 처리해야한다는 뜻이다
더 쉽게 말해서 3자리 단위로 끊어진다는 것

100 단위에서, 동전을 가장 적게 쓰는 방법은 DP로 구할 수 있다.
dp[현재 액수] = 1원 하나 쓰기 vs 10원 하나 쓰기 vs 25원 하나 쓰기
*/

#include <vector>
#include <algorithm>
using ull = unsigned long long;
ull dp[101];
vector<ull> inputs;
vector<ull> coins;

void solve()
{
	for (int i = 1; i <= 100; ++i)
	{
		dp[i] = dp[i - 1] + 1;
		//1원짜리 하나 추가하기 vs 10원짜리 하나 추가하기
		if (i >= 10) { dp[i] = min(dp[i], dp[i - 10] + 1); }

		//1원 추가 vs 10원 추가 vs 25원 추가
		if (i >= 25) { dp[i] = min(dp[i], dp[i - 25] + 1); }
	}
	
	ull T; cin >> T;
	while (T--)
	{
		ull cost; cin >> cost;
		ull count = 0;
		while (0 < cost)
		{
			count += dp[cost % 100];
			cost /= 100;
		}
		cout << count << '\n';
	}
}