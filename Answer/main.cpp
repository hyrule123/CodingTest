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
uint64 Factorial(uint64 _num) {
    //!!중요!! 0! == 1
    if (_num <= 1) {
        return 1ull;
    }

    return _num * Factorial(_num - 1ull);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint64 N{}, K{}; std::cin >> N >> K;
    //N C K -> N! / ( K!(N - K)! )
    std::cout << Factorial(N) / (Factorial(K) * Factorial(N - K));

    return 0;
}
