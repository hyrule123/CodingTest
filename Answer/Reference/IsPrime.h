//399949993 테스트해볼것


constexpr inline bool IsPrime(size_t _num) {
    if (_num <= 1) return false; // 1 and numbers less than 1 are not prime
    if (_num <= 3) return true; // 2 and 3 are prime

    if (_num % 2 == 0 || _num % 3 == 0) return false; // multiples of 2 and 3 are not prime

    // We only need to check divisors up to sqrt(n)
    //int maxDivisor = sqrt(_num);

    // We start from 5 and increment by 6 (since all primes greater than 3 are of the form 6k ± 1)
    for (int i = 5; i * i <= _num; i += 6) {
        if (_num % i == 0 || _num % (i + 2) == 0) {
            return false; // If n is divisible by i or i+2, then it's not prime
        }
    }

    return true; // If n is not divisible by any divisor up to sqrt(n), then it's prime
}





#include <vector>
using ull = std::uint64_t;
inline std::vector<bool> RangedErastothenes(ull _start, ull _end) {
    std::vector<bool> sieve{};
    sieve.reserve(_end + 1);
    sieve.resize(_start, false); //start까지는 측정 x
    sieve.resize(_end + 1, true);

    if (sieve.size() >= 2) {
        sieve[0] = false;
        sieve[1] = false;
    }

    for (size_t p = 2, pPow2{}; (pPow2 = p * p) <= _end; ++p) {
        //시작점 = start 이후의 최초 p의 배수 또는 p의 제곱
        //start + p - 1 : p를 더해주고, p를 더해줬을 때 나눠떨어지면 안되니까 1을 빼줌 -> 몫이 1 더 늘어나는걸 방지
        //p로 나눠준 뒤 다시 p를 곱해주면 최초 p의 배수가 된다.
        ull current = std::max((_start + p - 1) / p * p, pPow2);

        //p의 배수들을 모조리 false 처리한다.
        for (size_t i = current; i <= _end; i += p) {
            sieve[i] = false;
        }
    }

    return sieve;
}