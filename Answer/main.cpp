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
백준 10830 (행렬 제곱) [복습]
*/
#include <vector>
#include <array>
using ll = long long;
ll N, B;
constexpr int mod = 1000;
struct matrix {
	int m[5][5]{};
	matrix operator *(const matrix& other) {
		matrix ret;
		for (int row = 0; row < N; ++row) {
			for (int col = 0; col < N; ++col) {
				int& cur = ret.m[row][col];
				for (int i = 0; i < N; ++i) {
					cur += m[row][i] * other.m[i][col];
					cur %= mod;
				}
			}
		}
		return ret;
	}
};

constexpr matrix IDENTITY = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
};

void solve() {
	cin >> N >> B;

	matrix mat_bin = IDENTITY;
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			cin >> mat_bin.m[r][c];
		}
	}

	matrix mat = IDENTITY;
	if (B & (1ll << 0ll)) {
		mat = mat * mat_bin;
	}
	//2, 4, 8, 16, ...
	for (ll exp_bin = 1; exp_bin < 64; ++exp_bin) {
		const ll exp = 1ll << exp_bin;
		if (exp > B) { break; }

		mat_bin = mat_bin * mat_bin;
		if (exp & B) {
			mat = mat * mat_bin;
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << mat.m[i][j] << ' ';
		}
		cout << '\n';
	}
}