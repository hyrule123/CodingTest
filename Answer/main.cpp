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
inline uint64 Pow(uint64 _base, uint64 _exp) {
    uint64 ret = 1;
    
    for (uint64 i = 0; i < _exp; ++i) {
        ret *= _base;
    }

    return ret;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint64 N{}; std::cin >> N;
    std::cout << Pow(2ull , N);

    return 0;
}
