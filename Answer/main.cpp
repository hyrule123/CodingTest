#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint64 = std::uint64_t;
std::vector<uint64> waitTime;

void Heapify(const uint64 _size, const uint64 _idx) {
	uint64 parent = _idx;
	uint64 left = _idx * 2 + 1;
	uint64 right = left + 1;

	if (left < _size && waitTime[parent] <= waitTime[left]) {
		parent = left;
	}
	if (right < _size && waitTime[parent] <= waitTime[right]) {
		parent = right;
	}

	if (_idx != parent) {
		std::swap(waitTime[_idx], waitTime[parent]);
		Heapify(_size, parent);
	}
}

void HeapSort() {
	if (waitTime.size() < 2) { return; }

	for (uint64 i = (uint64)waitTime.size() / 2; i != -1; --i) {
		Heapify((uint64)waitTime.size(), i);
	}

	for (uint64 i = (uint64)waitTime.size() - 1; i >= 1; --i) {
		std::swap(waitTime[0], waitTime[i]);
		Heapify(i, 0);
	}
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	uint64 N; std::cin >> N;
	waitTime.resize(N);
	for (uint64 i = 0; i < N; ++i) {
		std::cin >> waitTime[i];
	}
	HeapSort();

	uint64 sum = 0;
	for (uint64 i = 0; i < N; ++i) {
		sum += waitTime[i] * (N - i);
	}
	std::cout << sum;
	return 0;
}
