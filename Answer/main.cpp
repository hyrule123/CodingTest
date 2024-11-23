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
백준 1020 (디지털 카운터)
*/

#include <string>
#include <vector>
using ll = long long;
constexpr ll
line_counts[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 },
diff[] = { 1, -4, 3, 0, -1, 1, 1, -3, 4, -2 };

void solve() {
	vector<ll> num;
	{
		string input; cin >> input;
		num.resize(input.size());
		for (size_t i = 0; i < input.size(); ++i) {
			num[i] = (int)(input[i] - '0');
		}
	}

	ll sum = 0;
	for (ll l : num) {
		sum += line_counts[l];
	}
	const ll orig = sum;

	ll counter = 0;
	while (true) {
		++counter;
		for (ll i = (ll)num.size() - 1; i >= 0; --i) {
			num[i] = (num[i] + 1) % 10;
			sum += diff[num[i]];
			if (num[i] != 0) { break; }
		}

		if (orig == sum) {
			break;
		}
	}
	cout << counter;
}