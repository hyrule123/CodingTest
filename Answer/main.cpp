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

using uint64 = std::uint64_t;
uint64 Factorial(uint64 _num, uint64 _range) {
    uint64 ret = 1;

    for (uint64 i = 0; i < _range; ++i) {
        ret *= _num;
        --_num;
    }

    return ret;
}

uint64 Combination(uint64 _items, uint64 _selections) {
    uint64 range = std::min(_selections, _items - _selections);
    return Factorial(_items, range) / Factorial(range, range);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int T{}; std::cin >> T;
    for (int i = 0; i < T; ++i) {
        uint64 N{}, M{}; std::cin >> N >> M;
        std::cout << Combination(M, N) << '\n';
    }

    return 0;
}
