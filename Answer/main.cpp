#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}
/*
백준 1010 (Fly me to the Alpha Centauri)
시작 1, 끝이 1이므로
중간까지 가속을 진행하다가 중간 시점부터 다시 줄여서 도착 직전에 속도를 2 또는 1까지 줄여야 함
이동횟수별 최대 이동거리를 넘어갈 경우 Count를 1회 추가해줘야 한다
				  max_count dist MAX
0				->0,	0
1				->1,	1	(+1)
1 1				->2,	2	(+1)
1 2 1			->3,	4	(+2) 
1 2 2 1			->4,	6	(+2)
1 2 3 2 1		->5,	9	(+3)
1 2 3 3 2 1		->6,	12	(+3)
1 2 3 4 3 2 1	->7,	16	(+4)
구해야 하는것: 주어진 distance가 어느 범위에 속하는지(max_count)
ex. 13 -> 6과 7 사이이므로 7
현재 수열에서 가장 큰값 MAX = sqrt(dist) = (max_count + 1) / 2
max_count = sqrt(dist) * 2 - 1
count가 정수이면->max_count
count가 정수가 아니면 -> max_count + 1
*/

#include <queue>
#include <cmath>
using ull = unsigned long long;

void solve() {
	ull T; cin >> T;
	while (T--) {
		ull x, y; cin >> x >> y;

		double dist = (double)(y - x);
		double max_count = sqrt(dist) * 2.0 - 1.0;

		//최대값을 넘어갈경우 +1
		if (floor(max_count) < max_count) {
			cout << (ull)max_count + 1 << '\n';
		}
		else {
			cout << (ull)max_count << '\n';
		}
	}
}