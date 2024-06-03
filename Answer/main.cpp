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

//LIS 확인 시간복잡도 O(logN)인 버전
#include <vector>
#include <stack>
using uint = unsigned int;
size_t SearchDP(std::vector<uint>& _dp, uint _u) {
	size_t start = 0;
	size_t end = _dp.size();
	size_t mid = end / 2;
	while (start < end && 0 < mid) {
		if (_dp[mid - 1] < _u && _u <= _dp[mid]) { break; }
		if (_dp[mid] < _u) { start = mid; }
		else { end = mid; }
		mid = (start + end) / 2;
	}
	return mid;
}

//return val: 이번에 들어온 _u의 LIS 길이
size_t InsertDP(std::vector<uint>& _dp, uint _u) {
	if (_dp.empty() || _dp.back() < _u) {
		_dp.push_back(_u);
		return _dp.size();
	}
	size_t idx = SearchDP(_dp, _u);
	_dp[idx] = _u;
	return idx + 1;
}

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	size_t N{}; std::cin >> N;
	std::vector<uint> inputs(N);
	std::vector<uint> leftLIS; leftLIS.reserve(N);
	std::vector<uint> rightLIS; leftLIS.reserve(N);

	for (size_t i = 0; i < N; ++i) {
		std::cin >> inputs[i];
	}

	size_t max = 2;
	for (size_t i = 0; i < N; ++i) {
		//이번에 넣은 값이 몇개의 수열을 만들수있는지 확인
		
		//dpLeft는 하나씩 추가해가면서 
		size_t sum = InsertDP(leftLIS, inputs[i]);

		//dpRight는 매번 새로 만들어준다.(되돌릴 방법을 모르겠음, stack 써야되나)
		rightLIS.clear();
		for (size_t j = N - 1; j > i; --j) {
			InsertDP(rightLIS, inputs[j]);
		}
		sum += InsertDP(rightLIS, inputs[i]);

		max = std::max(max, sum);
	}

	std::cout << max - 1;

	return 0;
}
