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

//Euclidean algorithm
std::uint32_t GCD(std::uint32_t _a, std::uint32_t _b) {
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

    std::uint32_t nomA{}, denomA{}, nomB{}, denomB{};
    std::cin >> nomA >> denomA >> nomB >> denomB;

    std::uint32_t nomAB = nomA * denomB + nomB * denomA;
    std::uint32_t denomAB = denomA * denomB;
    std::uint32_t gcd = GCD(nomAB, denomAB);
    
    std::cout << nomAB / gcd << ' ' << denomAB / gcd;

    return 0;
}
