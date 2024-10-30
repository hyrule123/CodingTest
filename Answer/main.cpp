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

int N, S, arr[100001]; 
constexpr int MAX = (int)1e9;
void solve() {
	cin >> N >> S;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}

	int l = 0, r = 0, cur_sum = arr[0], shortest_len = MAX;
	while (l < N && r < N) {
		while (r < N && cur_sum < S) {
			++r;
			cur_sum += arr[r];
		}

		while (l < N && S <= cur_sum - arr[l]) {
			cur_sum = cur_sum - arr[l];
			++l;
		}
		
		if (S <= cur_sum) {
			shortest_len = min(shortest_len, r - l + 1);
			if (r < N) {
				++r;
				cur_sum += arr[r];
			}
			if (l < r) {
				cur_sum -= arr[l];
				++l;
			}
		}
	}

	if (MAX == shortest_len) {
		cout << 0;
	}
	else {
		cout << shortest_len;
	}
}