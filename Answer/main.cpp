#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1644 (소수의 연속합) - 다른 분 해답 참고
*/
#include <vector>
#include <cmath>
using ull = unsigned long long;
std::vector<ull> get_prefix_sum_primes(ull _n) {
	std::vector<ull> ret;
	ret.reserve(_n / ((ull)std::log(_n) + 1));

	std::vector<bool> sieve(_n + 1, true);
	sieve[0] = sieve[1] = false;
	for (ull i = 2; i * i <= _n; ++i) {
		if (sieve[i]) {
			for (ull j = i * i; j <= _n; j += i) {
				sieve[j] = false;
			}
		}
	}

	ret.push_back(0);
	for (ull i = 2; i <= _n; ++i) {
		if (sieve[i]) {
			ret.push_back(i);
			*(ret.end() - 1) += *(ret.end() - 2);
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
	std::vector<ull> prefix_sum = get_prefix_sum_primes(N);

	//투 포인터
	ull max = (ull)prefix_sum.size() - 1;
	ull l = 0;
	ull r = 1;
	ull sum = prefix_sum[0];
	ull ans_count = 0;
	while (r <= max) {
		ull part_sum = prefix_sum[r] - prefix_sum[l];

		if(part_sum < N) {
			++r;
		}
		else if (N < part_sum) {
			++l;
		}
		else {
			++ans_count;
			++l;
			++r;
		}
	}

	std::cout << ans_count;

	return 0;
}