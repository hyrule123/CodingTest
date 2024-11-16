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

//백준 17435 (합성함수와 쿼리) [LCA 기초지식]
#include <cmath>

//f[n][x]
//n: 이진법 비트시프트 횟수(1<<1, 1<<2, ...1<<19)
//십진법일 때
// f[8][x] = f[4][f[4][x]] = f[4][f[2][f[2][x]]] = f[4][f[2][f[1][f[1][x]]]]...
// f[1<<3]... = f[1<<2]... = f[1<<1]... f[1<<0]...
constexpr int bin_lift = 19;
int m, f[bin_lift][200001], Q;

void solve() {
	//double l2 = ceil(log2(500000)); //19

	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> f[0][i];
	}

	//precompute
	for (int i = 1; i < bin_lift; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
	

	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		int n, x; cin >> n >> x;

		//미리 계산된 데이터를 활용, 값을 구함
		for (int j = 0; j < 19; ++j) {
			int bit = 1 << j;
			if (n < bit) { break; }
			if (n & (1 << j)) {
				x = f[j][x];
			}
		}

		cout << x << '\n';
	}
}