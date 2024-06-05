#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
std::vector<int> LIS; 

void InsertLIS(int _val) {
	if (LIS.back() < _val) { LIS.push_back(_val); return; }
	size_t start = 0;
	size_t end = LIS.size();
	size_t mid = LIS.size() / 2;
	while (start < end) {
		if (LIS[mid - 1] < _val && _val <= LIS[mid]) {
			LIS[mid] = _val;
			break;
		}
			
		if (LIS[mid] <= _val) {
			start = mid;
		}
		else {
			end = mid;
		}
		mid = (start + end) / 2;
	}
}

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	size_t N; std::cin >> N;
	std::vector<int> inputs(501, -1);
	for (size_t i = 0; i < N; ++i) {
		int idx, val; std::cin >> idx >> val;
		inputs[idx] = val;
	}

	LIS.reserve(N + 1); LIS.push_back(0);
	for (size_t i = 0; i < 501; ++i) {
		if (0 <= inputs[i]) {
			InsertLIS(inputs[i]);
		}
	}
	std::cout << N - (LIS.size() - 1);

	return 0;
}
