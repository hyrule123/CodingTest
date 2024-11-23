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
백준 1009 (분산처리)
*/
#include <vector>
//by chatgpt -> 제곱수의 cyclic pattern을 이용한 풀이
// Precompute the cycle of last digits for each possible a (0 to 9)
vector<int> cycles[10] = {
	{0},        // 0^b is always 0
	{1},        // 1^b is always 1
	{2, 4, 8, 6},
	{3, 9, 7, 1},
	{4, 6},
	{5},        // 5^b is always 5
	{6},        // 6^b is always 6
	{7, 9, 3, 1},
	{8, 4, 2, 6},
	{9, 1}
};

void solve() {
	int T; cin >> T;
	while (T--) {
		size_t a, b; cin >> a >> b;

		a %= 10;
		//b^1부터 시작이므로 b에선 1을 빼준다
		//ex. 12^2 -> cycles[2][(2 - 1) % 4]
		size_t ans = cycles[a][(b - 1) % cycles[a].size()];
		if (ans == 0) { ans = 10; }
		cout << ans << '\n';
	}
}