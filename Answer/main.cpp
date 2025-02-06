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
백준 23250 (하노이 탑 K) [오답-시간 초과]
*/
using ull = unsigned long long;
ull N, K, cur;
//N번 원판을 옮기고 싶다
void recursive(ull level, ull from, ull to, ull temp)
{
	if (level < 1) { return; }


	//그럼일단 내 위의 원판(N-1번) 원판을 전부 임시 봉으로 옮겨야 한다
	recursive(level - 1, from, temp, to);

	//내 원판을 목표로 옮긴다
	//이번 작업이 K번째 작업이라면 출력하고 리턴
	++cur;
	if (cur == K)
	{
		cout << from << ' ' << to;
		return;
	}

	//임시 봉에 있던 원판을 다시 원상복구한다.
	recursive(level - 1, temp, to, from);
}

void solve()
{
	cin >> N >> K;

	recursive(N, 1, 3, 2);
}