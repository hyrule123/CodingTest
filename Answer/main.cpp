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
백준 14238 (출근 기록) [그리디]
https://oculis.tistory.com/55
오답 원인: 단순하게 C를 최우선으로 두면 된다고 생각했는데,
"BBC" 와 같이 B의 우선순위를 높여야 하는 경우를 생각하지 못했음.
당연히 가장 까다로운 C를 우선적으로 처리해야 하는 것은 맞지만,
특정 상황에는 B가 와 주어야 한다.
B가 충분히 남아 있는 경우(B가 남은 길이의 반 이상보다 많은 경우) B를 먼저 사용하도록 해 주면 된다.
*/

#include <string>
constexpr int A = 0, B = 1, C = 2;
string str;
int ABC[3], total, B_cooltime, C_cooltime;

void solve()
{
	cin >> str;
	for (char c : str)
	{
		ABC[c - 'A']++;
		total++;
	}

	str.clear();
	for(int i = 0; i < total; ++i)
	{
		if (0 > --B_cooltime) { B_cooltime = 0; }
		if (0 > --C_cooltime) { C_cooltime = 0; }

		int remain_half = (total - i) / 2;
		if (0 == C_cooltime && 0 < ABC[C] && ABC[B] <= remain_half)
		{
			str.push_back('C');
			ABC[C]--;
			C_cooltime = 3;
		}
		else if (0 == B_cooltime && 0 < ABC[B])
		{
			str.push_back('B');
			ABC[B]--;
			B_cooltime = 2;
		}
		else
		{
			if (ABC[A] <= 0)
			{
				cout << -1;
				return;
			}

			str.push_back('A');
			ABC[A]--;
		}
	}

	cout << str;
}