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
백준 24390 (또 전자레인지야?) [그리디]
* 조리버튼을 먼저 누르고 시작하는 경우(-30초)
* 먼저 분을 맞추고 + 마지막에 조리시작 버튼을 누르는 경우
*/
int times[] = { 600, 60, 10 };
int check_count(int sec)
{
	int count = 1;	//조리버튼 먼저 카운트
	for (const int t : times)
	{
		while (t <= sec)
		{
			sec -= t;
			++count;
		}
	}
	return count;
}

void solve()
{
	int m, s; char c;
	cin >> m >> c >> s;
	s += m * 60;

	//30초 딱코는 그냥 조리버튼 한번 누르면 됨
	if (s == 30)
	{
		cout << 1;
		return;
	}

	int jori_later = check_count(s);
	int jori_first = 10000;
	if (30 < s)
	{
		jori_first = check_count(s - 30);
	}

	cout << min(jori_first, jori_later);
}