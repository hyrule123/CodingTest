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
using uint64 = std::uint64_t;
inline std::vector<bool> RangedErastothenes(uint64 _start, uint64 _end) {
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
        uint64 current = std::max((_start + p - 1) / p * p, pPow2);

        //p의 배수들을 모조리 false 처리한다.
        for (size_t i = current; i <= _end; i += p) {
            sieve[i] = false;
        }
    }

    return sieve;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint64 begin{}, end{};
    std::cin >> begin >> end;

    auto vec = RangedErastothenes(begin, end);

    for (size_t i = begin; i <= end; ++i) {
        if (vec[i]) {
            std::cout << i << '\n';
        }
    }

    return 0;
}
