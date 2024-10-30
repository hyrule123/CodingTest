#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

using namespace std;
#include <algorithm>
#include <vector>
using ull = std::uint64_t;

void solve() {
	ull stock, target; cin >> stock >> target;
	vector<ull> wires; wires.resize(stock);

	ull start = 1, end = 1;
	for (ull& wire : wires) {
		cin >> wire;

		//end를 최대 길이로 설정해야하는 이유
		//500, 500, 500, 500, 50005, 5개 필요
		if (end < wire) {
			end = wire;
		}
	}
	
	while (start <= end) {
		ull mid = (start + end) / 2;
		ull count = 0;

		for (ull wire : wires) {
			count += wire / mid;
		}

		if (count < target) {
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}
	cout << end;
}