#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset

/*복습 - 골드바흐 파티션*/
#include <vector>
using uint = unsigned int;
std::vector<uint> inputs;
std::vector<bool> sieve;
void ComputeSieve(uint _n) {
	sieve.resize(_n + 1, true);
	if (0 < _n) { sieve[0] = false; }
	if (1 < _n) { sieve[1] = false; }

	for (uint i = 2; i * i <= _n; ++i) {
		if (sieve[i]) {
			for (uint j = i + i; j <= _n; j += i) {
				sieve[j] = false;
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	uint N, primeMax = 0; std::cin >> N;
	inputs.resize(N);
	for (uint i = 0; i < N; ++i) {
		std::cin >> inputs[i];
		if (primeMax < inputs[i]) {
			primeMax = inputs[i];
		}
	}

	ComputeSieve(primeMax);
	
	for (uint i = 0; i < N; ++i) {
		uint goldbachCount = 0;
		for (uint j = 2; j * 2 <= inputs[i]; ++j) {
			//j가 소수 + (인풋값 짝수) - j가 소수이면 골드바흐 파티션이 성립
			if (sieve[j] && sieve[inputs[i] - j]) {
				++goldbachCount;
			}
		}
		std::cout << goldbachCount << '\n';
	}

	return 0;
}