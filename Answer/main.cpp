#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//분할 정복 풀이
#include <vector>
using ll = long long;
std::vector<ll> histogram;
ll Recursive(ll _start, ll _end) {
	if (_start == _end) { return histogram[_start]; }

	ll mid = (_start + _end) / 2;
	ll square = histogram[mid];
	ll minHeight = histogram[mid];
	ll width = 1;

	//mid 막대기부터 왼쪽, 오른쪽 막대 중 긴걸로 하나씩 붙여가면서 최댓값을 비교한다.
	ll l = mid - 1;
	ll r = mid + 1;
	while (_start <= l && r <= _end) {
		if (histogram[l] < histogram[r]) {
			if (histogram[r] < minHeight) { minHeight = histogram[r]; }
			++r;
		}
		else {
			if (histogram[l] < minHeight) { minHeight = histogram[l]; }
			--l;
		}

		++width;
		square = std::max(square, minHeight * width);
	}

	//둘 중 한쪽이 끝났을 경우 남은 범위를 처리(mergesort와 비슷)
	for (; _start <= l; --l) {
		if (histogram[l] < minHeight) { minHeight = histogram[l]; }
		++width;
		square = std::max(square, minHeight * width);
	}
	for (; r <= _end; ++r) {
		if (histogram[r] < minHeight) { minHeight = histogram[r]; }
		++width;
		square = std::max(square, minHeight * width);
	}

	//현재 범위 중간부터 시작한 직사각형/좌측 직사각형/우측 직사각형 중 최대값 비교
	square = std::max(square, Recursive(_start, mid));
	square = std::max(square, Recursive(mid + 1, _end));
	return square;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;
	
	while (true) {
		ll input; std::cin >> input;
		if (0 == input) { break; }

		histogram.resize(input);
		for (ll i = 0; i < input; ++i) {
			std::cin >> histogram[i];
		}

		std::cout << Recursive(0, histogram.size() - 1) << '\n';
	}

	return 0;
}
