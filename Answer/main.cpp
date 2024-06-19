#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////


//참고 사이트
//https://velog.io/@junttang/BOJ-11401-%EC%9D%B4%ED%95%AD-%EA%B3%84%EC%88%98-3-%ED%95%B4%EA%B2%B0-%EC%A0%84%EB%9E%B5-C

//페르마의 소정리를 사용해야 함.
//N^p는 N과 합동이다(p로 나눈 나머지가 같다)
//N^(p-1)는 1과 합동이다(p로 나누면 나머지가 1이다)
//N^(p-2)는 N^-1과 합동이다(p로 나눈 나머지가 같다)

//나머지 연산은 곱셈과 덧셈에 분배법칙이 적용되지만, 나눗셈에는 적용할 수 없다.
//그러므로 나눗셈(분모) 연산이 있는 조합 수식에 대해서는 페르마의 소정리를 적용할 수 없다.
//여기서 페르마의 소정리를 해야 하는것
//nCr == n! * ( (r!) * (n - r)! )^-1 를 p로 나눈 나머지는
//== n! * ( (r!) * (n - r)! ) ^ (p-2) 를 p로 나눈 나머지와 같다.
//곱셈의 형태가 되었으므로, 나머지 연산의 분배법칙이 사용 가능해진다.

//여기에 추가로 조합의 약분을 활용해서 추가 최적화가 가능

#include <vector>
#include <array>
using uint64 = unsigned long long;
constexpr uint64 mod = 1'000'000'007;
uint64 FactorialRangedMod(uint64 _u, uint64 _range) {
	uint64 ret = 1;

	for (uint64 i = 0; i < _range; ++i) {
		ret = (ret * _u) % mod;
		--_u;
	}

	return ret;
}

//DP를 활용한 거듭제곱
uint64 PowMod(uint64 _base, uint64 _exp) {
	if (_exp == 0) { return 1; }
	else if (_exp == 1) { return _base; }
	
	//2^0
	uint64 prev = _base % mod;
	uint64 cur = 0;
	uint64 ret = 1;
	if (1 & _exp) { ret = prev; }
	
	for (uint64 i = 1; i < 64; ++i) {
		uint64 bit = 1ull << i;
		if (bit > _exp) { break; }
		cur = (prev * prev) % mod;

		if (bit & _exp) { 
			ret = (ret * cur) % mod;
		}

		prev = cur;
	}

	return ret;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	uint64 N, K; std::cin >> N >> K;

	//n! * ( (r!) * (n - r)! ) ^ (p-2)
	//여기에 약분 활용
	//r과 n-r중 작은걸 저장하고
	//n! -> n * n-1 * ... min(r, n-r): n을 둘중 짧은거만큼만 팩토리얼
	//(r!) * (n - r)! -> min(r, n-r)!: 둘중 짧은거 팩토리얼
	uint64 shorter = std::min(K, N - K);

	uint64 output = FactorialRangedMod(N, shorter);
	output = (output * PowMod(FactorialRangedMod(shorter, shorter), mod - 2)) % mod;
	std::cout << output;

	return 0;
}
