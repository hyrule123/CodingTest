#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//참고: 나무위키
//행렬로 피보나치 계산하기
//F2 F1		1 1
//		== 
//F1 F0		1 0
//이 행렬 m을 거듭제곱 하면
//m^n == F(n+1) F(n)
//		 F(n)	F(n-1)

using ull = unsigned long long;
struct mat22 {
	ull m[4];

	ull* operator [](ull _row) { if (_row) { _row = 2; } return &(m[_row]); }
	mat22 operator *(const mat22& _other) const {
		mat22 ret{};

		ret.m[0] = (m[0] * _other.m[0] + m[1] * _other.m[2]) % 1'000'000'007;
		ret.m[1] = (m[0] * _other.m[1] + m[1] * _other.m[3]) % 1'000'000'007;
		ret.m[2] = (m[2] * _other.m[0] + m[3] * _other.m[2]) % 1'000'000'007;
		ret.m[3] = (m[2] * _other.m[1] + m[3] * _other.m[3]) % 1'000'000'007;

		return ret;
	}
};

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	mat22 output{ 1,0,0,1 };
	mat22 base{ 1,1,1,0 };
	ull exp; std::cin >> exp;
	if (exp == 0) { std::cout << 0; return 0; }
	if (exp & 1) { output = base; }

	for (ull i = 1; i < 64; ++i) {
		ull bit = 1ull << i;
		if (bit > exp) { break; }

		base = base * base;
		
		if (bit & exp) { output = output * base; }
	}
	std::cout << output[0][1];

	return 0;
}
