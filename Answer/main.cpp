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

inline std::uint32_t GCD(std::uint32_t _a, std::uint32_t _b) {
    std::uint32_t r{};
    while (_b != 0) {
        r = _a % _b;
        _a = _b;
        _b = r;
    }
    return _a;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    std::uint32_t N{};
    std::cin >> N;

    std::uint32_t first{};

    std::uint32_t prev{}, cur{};
    std::cin >> prev >> cur;

    first = prev;

    std::uint32_t gcd = cur - prev;
    prev = cur;

    //매 순회마다 간격을 해서 계속 최소공약수를 구해준다.
    for (std::uint32_t i = 2; i < N; ++i) {
        std::cin >> cur;
        gcd = GCD(gcd, cur - prev);
        prev = cur;
    }
    std::uint32_t last = cur;

    //last - first = 전체 거리
    //gcd = 심어야하는 간격
    //(전체 거리 / 심어야하는 간격) + 1 = 규칙적으로 심었을때 나오는 나무의 수
    //N: 현재 심어져있는 나무의 수
    std::cout << (last - first) / gcd + 1 - N;

    return 0;
}
