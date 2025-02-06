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
백준 23250 (하노이 탑 K) [재귀]
* 핵심: 최대 2^60번의 작업 중 K를 찾아야 한다
* 일일히 카운트해가며 찾으면 당연 시간 초과
* 찾기 위해서는 답이 나올수 없는 구간은 생략해야 한다
*/
using ull = unsigned long long;
ull N, K, cur;
//N번 원판을 옮기고 싶다
void recursive(ull level, ull from, ull to, ull temp)
{
	if (level < 1) { return; }
	if (cur > K) { return; }

	//이번 원판을 옮기는 비용: 2^level - 1
	ull count_to_move = (1ull << level) - 1;
	//이번 원판을 다 옮겨도 K번째가 되지 않는다면
	if (cur + count_to_move < K)
	{
		//과정을 생략한다
		cur = cur + count_to_move;
		return;
	}

	//내 원판을 옮길 수 있는 상태가 되려면 위에 있는 모든 원판을 치워야 함
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