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

#include <deque>
#include <bitset>
int N, M;
bitset<100001> types;
deque<int> qs;
void solve() {
	cin >> N;

	for (int i = 0; i < N; ++i) {
		bool b; cin >> b;
		types[i] = b;
	}
	for (int i = 0; i < N; ++i) {
		int input; cin >> input;
		if (!types[i]) {
			qs.push_back(input);
		}
	}

	cin >> M;
	int input;
	for (int i = 0; i < M; ++i) {
		cin >> input;

		qs.push_front(input);
		cout << qs.back() << ' ';
		qs.pop_back();
	}
}