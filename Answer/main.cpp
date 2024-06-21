#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using ull = unsigned long long;
struct hRect {
	ull maxHeight, width, square;
	hRect operator + (const hRect& _other) const {
		hRect ret{};
		ret.maxHeight = std::min(maxHeight, _other.maxHeight);
		ret.width = width + _other.width;
		ret.square = ret.maxHeight * ret.width;
		return ret;
	}
};
std::vector<ull> histogram;

hRect Recursive(ull& _maxSquare, ull _start, ull _end) {
	if (_start >= _end) {
		hRect ret{};
		ret.maxHeight = histogram[_start];
		ret.width = 1;
		ret.square = ret.maxHeight;
		return ret;
	}

	//분할 결과마다 최댓값을 기록
	ull mid = (_start + _end) / 2;
	hRect left = Recursive(_maxSquare, _start, mid);
	_maxSquare = std::max(_maxSquare, left.square);

	hRect right = Recursive(_maxSquare, mid + 1, _end);
	_maxSquare = std::max(_maxSquare, right.square);

	//반환값: 좌, 우 히스토그램을 합친 부분에서 가장 큰 직사각형 넓이
	return left + right;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;
	
	while (true) {
		ull input; std::cin >> input;
		if (0 == input) { break; }

		histogram.resize(input);
		for (ull i = 0; i < input; ++i) {
			std::cin >> histogram[i];
		}

		ull maxSquare = 0;
		hRect finalRect = Recursive(maxSquare, 0, histogram.size() - 1);

		//마지막 결과 비교
		maxSquare = std::max(maxSquare, finalRect.square);
		std::cout << maxSquare << '\n';
	}

	return 0;
}
