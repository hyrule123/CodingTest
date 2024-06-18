#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

using uint64 = std::uint64_t;
uint64 arr64[64]{};

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	uint64 A, B, C; std::cin >> A >> B >> C;

	//DP 방식
	//DP의 인덱스: 지수가 2의 거듭제곱일 때의 결과
	//arr64[0] = A^(2^0), arr64[1] = A^(2^1), arr64[2] = A^(2^2), ...
	
	//숫자 B가 지수
	//예를들어 B == 5라고 하면
	//A ^ 5 == A ^ (2^2 + 1) == A^4 * A^1 == arr64[2] * arr64[0]
	//메모리에 B는 이진법으로 저장되어 있으므로 -> 비트 연산자를 통해서 빠르게 곱해야 할 인덱스를 알아낼 수 있다
	uint64 mod = 1;
	arr64[0] = A % C;	//A ^(2^0) % C
	if (B & (1ull << 0ull)) { mod = arr64[0]; }

	for (uint64 i = 1; i < 64; ++i) {
		uint64 curBit = 1ull << i;	//2^i
		if (curBit > B) { break; }	//2^i > B일 경우 중단
		
		arr64[i] = arr64[i - 1] * arr64[i - 1] % C;	//DP
		if (curBit & B) { mod = (mod * arr64[i]) % C; }	//비트 연산을 통해 포함되는 자릿수일 경우 결과에 포함
	}

	std::cout << mod;

	return 0;
}
