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
백준 2502 (떡 먹는 호랑이) [dp]
계수 느낌으로 접근하자
dp[1] = 1a
dp[2] = 1b
dp[3] = 1a + 1b
dp[4] = 1a + 2b

*/
using pii = pair<int, int>;
#define coef_a first
#define coef_b second
pii dp[31];

void solve()
{
	dp[1] = { 1, 0 };
	dp[2] = { 0, 1 };

	for (int i = 3; i <= 30; ++i)
	{
		dp[i].coef_a = dp[i - 1].coef_a + dp[i - 2].coef_a;
		dp[i].coef_b = dp[i - 1].coef_b + dp[i - 2].coef_b;
	}

	int date, value; cin >> date >> value;
	//1 <= coef_a <= coef_b
	for (int a = 1; a <= value / dp[date].coef_a; ++a)
	{
		
		int b_val = (value - a * dp[date].coef_a);
		if (0 < b_val && 0 == (b_val % dp[date].coef_b))
		{
			cout << a << '\n' << (value - a * dp[date].coef_a) / dp[date].coef_b;
			return;
		}
	}
}