#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

////////////////////////////
#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
////////////////////////////

#include <vector>
#include <cmath>
inline std::vector<bool> ErastothensSieve(const size_t _end) {
    std::vector<bool> sieve{};
    sieve.resize(_end + 1, true);
    if (sieve.size() >= 1) { sieve[0] = false; }
    if (sieve.size() >= 2) { sieve[1] = false; }

    for (size_t p = 2, pPow2{}; (pPow2 = p * p) <= _end; ++p) {
        if (sieve[p]) {
            for (size_t i = pPow2; i <= _end; i += p) {
                sieve[i] = false;
            }
        }
    }
    
    return sieve;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using uint = unsigned int;
    std::vector<uint> inputs{};
    size_t N{};
    std::cin >> N;
    inputs.resize(N);

    uint biggest{};
    for (size_t i = 0; i < N; ++i) {
        std::cin >> inputs[i];
        if (biggest < inputs[i]) { biggest = inputs[i]; }
    }

    std::vector<uint> primes{};
    //대략적인 소수 개수 추측해서 reserve
    size_t logn = (size_t)std::log((double)biggest);
    if (logn == 0) { logn = 1; }
    primes.reserve(biggest / logn + 100);
    //에라스토테네스 체에서 판별된 소수들 집어넣는다.
    std::vector<bool> sieve = ErastothensSieve((size_t)biggest);
    for (size_t i = 0; i < sieve.size(); ++i) {
        if (sieve[i]) {
            primes.push_back((uint)i);
        }
    }

    for (size_t i = 0; i < inputs.size(); ++i) {
        size_t goldBachCounts{};

        //조건: input값의 반 이하인 소수
        for (size_t p1Idx = 0; 
            p1Idx < primes.size() && primes[p1Idx] * 2 <= inputs[i]; 
            ++p1Idx) {
            //input에서 소수를 뺴고, 남은 값이 소수인지 확인한다.
            //sieve의 인덱스로 넣으면 바로 알 수 있음.
            size_t p2 = inputs[i] - primes[p1Idx];
            if (sieve[p2]) {
                ++goldBachCounts;
            }
        }
        std::cout << goldBachCounts << '\n';
    }

    return 0;
}
