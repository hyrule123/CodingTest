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
백준 15973 (두 박스) [기하]
1. 우선 충돌여부를 제일 먼저 확인
*/

constexpr int L = 0, B = 1, R = 2, T = 3;
int P[4], Q[4];

void solve()
{
	cin >> P[L] >> P[B] >> P[R] >> P[T]
		>> Q[L] >> Q[B] >> Q[R] >> Q[T];

	//가장먼저 충돌 여부를 확인
	if (P[B] > Q[T] || P[L] > Q[R] || P[R] < Q[L] || P[T] < Q[B])
	{
		cout << "NULL";
		return;
	}

	//한 점만 겹침 여부를 확인
	bool point = false;

	//LB == RT
	point |= (P[L] == Q[R] && P[B] == Q[T]);

	//RT == LB
	point |= (P[R] == Q[L] && P[T] == Q[B]);

	//LT == RB
	point |= (P[L] == Q[R] && P[T] == Q[B]);

	//RB == LT
	point |= (P[R] == Q[L] && P[B] == Q[T]);
	if (point)
	{
		cout << "POINT";
		return;
	}


	//한 선만 겹침 여부를 확인
	bool line = (P[L] == Q[R] || P[R] == Q[L] || P[B] == Q[T] || P[T] == Q[B]);
	if (line)
	{
		cout << "LINE";
		return;
	}

	//다 아니면 FACE
	cout << "FACE";
}