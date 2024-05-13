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

#include <cmath>
using uint64 = std::uint64_t;
inline uint64 NextPrime(uint64 _num) {
    if (_num <= 1) { return 2; }
    if (_num <= 3) { return _num; }
    
    while (true) {
        if (_num % 2 == 0 || _num % 3 == 0) {
            ++_num;
            continue;
        }

        //The rounding error is at most one part in 2^53. 
        // This causes an error in the square root of at most one part in 2^54. 
        // The sqrt itself has a rounding error of less than one part in 2^53, due to rounding the mathematical result to the double format. 
        // The sum of these errors is tiny; the largest possible square root of a 64-bit integer (rounded to 53 bits) is 2^32, so an error of three parts in 2^54 is less than .00000072.
        //double 오차 가능성이 있으므로 1 더해줬음
        uint64 end = (uint64)std::sqrt((double)_num) + 1;

        bool isP = true;
        for (uint64 i = 5; i <= end; i += 6) {
            if (_num % i == 0 || _num % (i + 2) == 0) {
                ++_num;
                isP = false;
                break;
            }
        }

        if(isP){ break; }
    }
    return _num;
}


int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t tc{};
    std::cin >> tc;

    for (size_t i = 0; i < tc; ++i) {
        uint64 input{};
        std::cin >> input;

        std::cout << NextPrime(input) << '\n';
    }

    return 0;
}
