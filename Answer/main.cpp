#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint = unsigned int;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	uint N, M; std::cin >> N >> M;
	std::vector<uint> trees(N);
	uint start = 0, end{};	//톱의 최소 높이=0
	for (uint i = 0; i < N; ++i) {
		std::cin >> trees[i];
		if (end < trees[i]) { end = trees[i]; }
	}
	++end;

	while (start + 1 < end) {
		uint mid = (start + end) / 2;
		uint height = 0;
		for (uint i = 0; i < N; ++i) {
			//톱의 높이보다 나무가 길 경우에만 자를수 있다
			if (mid < trees[i]) {
				height += (trees[i] - mid);
			}
			//루프마다 종료조건 검사 안하면 오버플로우가 발생할 수 있다
			if (M < height) { break; }
		}

		if (M <= height) {
			start = mid;
		}
		else {
			end = mid;
		}
	}
	std::cout << start;

	return 0;
}