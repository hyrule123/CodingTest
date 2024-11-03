#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

int N, result[10];

void calc(int i) {
	while (i >= 10) {
		++(result[i % 10]);
		i /= 10;
	}
	++(result[i % 10]);
}

void solve() {
	cin >> N;
	while (1 <= N) {
		calc(N);
		--N;
	}

	for (int i : result) {
		cout << i << ' ';
	}
}