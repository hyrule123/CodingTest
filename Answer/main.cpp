#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////
using uint64 = std::uint64_t;

uint64 PowRecursive(uint64 _base, uint64 _exp, uint64 _mod) {
	if (_exp == 0) {
		return 1;
	}
	else if (_exp == 1) {
		return _base % _mod;
	}

	//2^5 = 2^2 * 2^2 * 2
	//앞에 2개 분할정복으로 재사용하고, 나머지 홀수부분은 따로 곱해준다
	bool isOdd = _exp % 2 == 1;
	if (isOdd) { --_exp; }
	uint64 ret = PowRecursive(_base, _exp / 2, _mod);
	ret = ret * ret % _mod;
	if (isOdd) { ret = ret * _base % _mod; }

	return ret;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	uint64 A, B, C; std::cin >> A >> B >> C;
	std::cout << PowRecursive(A, B, C);

	return 0;
}
