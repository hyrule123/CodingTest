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
inline std::uint64_t GCD(std::uint64_t _a, std::uint64_t _b) {
    std::uint64_t r{};
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
    
    std::uint64_t A{}, B{};
    std::cin >> A >> B;

    std::uint64_t gcd = GCD(A, B);
    std::cout << A * B / gcd << '\n';

    return 0;
}
