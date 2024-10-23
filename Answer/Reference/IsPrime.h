//399949993 �׽�Ʈ�غ���


constexpr inline bool IsPrime(size_t _num) {
    if (_num <= 1) return false; // 1 and numbers less than 1 are not prime
    if (_num <= 3) return true; // 2 and 3 are prime

    if (_num % 2 == 0 || _num % 3 == 0) return false; // multiples of 2 and 3 are not prime

    // We only need to check divisors up to sqrt(n)
    //int maxDivisor = sqrt(_num);

    // We start from 5 and increment by 6 (since all primes greater than 3 are of the form 6k �� 1)
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
    sieve.resize(_start, false); //start������ ���� x
    sieve.resize(_end + 1, true);

    if (sieve.size() >= 2) {
        sieve[0] = false;
        sieve[1] = false;
    }

    for (size_t p = 2, pPow2{}; (pPow2 = p * p) <= _end; ++p) {
        //������ = start ������ ���� p�� ��� �Ǵ� p�� ����
        //start + p - 1 : p�� �����ְ�, p�� �������� �� ������������ �ȵǴϱ� 1�� ���� -> ���� 1 �� �þ�°� ����
        //p�� ������ �� �ٽ� p�� �����ָ� ���� p�� ����� �ȴ�.
        ull current = std::max((_start + p - 1) / p * p, pPow2);

        //p�� ������� ������ false ó���Ѵ�.
        for (size_t i = current; i <= _end; i += p) {
            sieve[i] = false;
        }
    }

    return sieve;
}