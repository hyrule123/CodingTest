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

//399949993 테스트해볼것