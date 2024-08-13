#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1644 (소수의 연속합)
*/
#include <vector>
#include <cmath>
using ull = unsigned long long;
std::vector<ull> Sieve(ull _n) {
	std::vector<ull> ret;
	ret.reserve(_n / ((ull)std::log(_n) + 1));

	std::vector<bool> sieve(_n + 1, true);
	sieve[0] = false;
	sieve[1] = false;
	for (ull i = 2; i <= _n; ++i) {
		if (sieve[i]) {
			ret.push_back(i);

			for (ull j = i + i; j <= _n; j += i) {
				sieve[j] = false;
			}
		}
	}

	return ret;
}
ull N;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	if (N <= 1) {
		std::cout << 0;
		return 0;
	}

	//에라스토테네스의 체
	std::vector<ull> primes = Sieve(N);

	//투 포인터
	ull max = (ull)primes.size() - 1;
	ull l = 0;
	ull r = 0;
	ull sum = primes[0];
	ull ans_count = 0;
	while (true) {
		if (sum < N) {
			if (r < max) {
				sum += primes[++r];
			}
			else { break; }
		}
		else if (N < sum) {
			if (l <= r) {
				sum -= primes[l]; ++l;
			}
			else { break; }
		}
		else { // sum == N
			++ans_count;

			if (r < max) {
				sum += primes[++r];
			}
			else { break; }

			if (l <= r) {
				sum -= primes[l]; ++l;
			}
			else { break; }
		}
	}

	std::cout << ans_count;

	return 0;
}