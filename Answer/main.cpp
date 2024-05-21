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

using uint64 = std::int64_t;
uint64 Factorial(uint64 _num) {
    if (_num <= 1) { return 1; }

    return _num * Factorial(_num - 1);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint64 input{}; std::cin >> input;
    std::cout << Factorial(input);
    
    return 0;
}
