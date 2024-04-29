#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
#include <limits>

#include <vector>

inline void ChangeBoolInterval(std::vector<bool>& _vec, size_t _idxStart, const size_t _interval, bool _b)
{
    size_t vecSize = _vec.size();
    for (_idxStart; _idxStart < vecSize; _idxStart += _interval)
    {
        _vec[_idxStart] = _b;
    }
}

//에라스토테네스의 체 코드 분석용
std::vector<bool> EratosthenesSieve(size_t _maxNum)
{
    std::vector<bool> sieve{};
    sieve.resize(++_maxNum);

    //2와 3은 소수이다
    if (2 < _maxNum)
    {
        sieve[2] = true;
    }
    if (3 < _maxNum)
    {
        sieve[3] = true;
    }
    

    //2와 3을 약수로 가지고 않은 숫자집합을 true로 설정한다.(소수 가능성이 있는애들 true)
    //P = { 1, 5 } + 6n // not divisible 2, 3
    //residue class modulo 6
    ChangeBoolInterval(sieve, 5, 6, true);
    ChangeBoolInterval(sieve, 7, 6, true);

    //루프를 돌며 위의 숫자들 중에서 소수가 아닌 수를 걸러낸다.
    for (size_t i = 5, ipow2 = 25; ipow2 < sieve.size();)
    {
        //i = 5, 7, 11, 13, 17, 19, 23, 25...
        //2 더하고 4 더하고 반복
        size_t next = (i - 3) % 6;

        //i가 소수이면, i의 배수들은 소수가 될 수 없다.
        if (sieve[i])
        {
            //P = {1, 7, 11, 13, 17, 19, 23, 29} + 30 * n // not divisble by 2, 3, 5
            size_t newMod = i * 6;

            //i가 소수->ipow2 + i * 6 * n은 무조건 i로 나눠 떨어진다(i + 6n)
            ChangeBoolInterval(sieve, ipow2, newMod, false);
            
            //next * i + i^2 + i * 6 * n를 i로 나눠주면
            //next + i + 6n으로 나눠 떨어진다.
            //ex) 5 * 7 + 5 * 5
            //7 * 4 + 7 * 7
            ChangeBoolInterval(sieve, ipow2 + next * i, newMod, false);
        }

        //다음 루프 준비
        i += next;
        ipow2 = i * i;
    }

    return sieve;
}

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    int M{}, N{};
    std::cin >> M >> N;
    
    std::vector<bool> sieve = EratosthenesSieve(N);

    int minPrime{};
    int sumPrime{};

    ++N;
    for (int i = M; i < N; ++i)
    {
        if (sieve[i])
        {
            if (0 == minPrime)
            {
                minPrime = i;
            }

            sumPrime += i;
        }
    }

    if (0 == sumPrime)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << sumPrime << '\n' << minPrime;
    }
    return 0;
}
