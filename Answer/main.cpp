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
백준 23317 (구슬 굴리기) [DP]
* 각 row에는 row개수만큼의 공간(row size == col size)
*/
#include <vector>
#include <array>
int row_size, must_pass_size;
array<array<int, 30>, 30> dp;
array<vector<int>, 30> must_passes;
bool is_valid(int row, int col) {
	return 0 <= row && 0 <= col && col <= row;
}

void solve() {
	cin >> row_size >> must_pass_size;
	for (int i = 0; i < must_pass_size; ++i) {
		int row, col; cin >> row >> col;
		must_passes[row].push_back(col);
	}

	dp[0][0] = 1;
	for (int r = 1; r < row_size; ++r) {
		for (int c = 0; c <= r; ++c) {
			int from_left = is_valid(r - 1, c - 1) ?
				dp[r - 1][c - 1] : 0;
			int from_right = is_valid(r - 1, c) ? 
				dp[r - 1][c] : 0;
			
			dp[r][c] = from_left + from_right;
		}

		//반드시 지나야 하는 곳이 이번 행에 있다면 그곳을 제외하고 0으로 초기화한다.
		if (false == must_passes[r].empty()) {
			array<int, 30> temp = dp[r];
			dp[r].fill(0);
			for (int i = 0; i < (int)must_passes[r].size(); ++i) {
				dp[r][must_passes[r][i]] = temp[must_passes[r][i]];
			}
		}
	}

	int ans = 0;
	for (int c = 0; c < row_size; ++c) {
		ans += dp[row_size - 1][c];
	}
	cout << ans;
}