#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

using uint = unsigned int;
#include <vector>
uint FibRecursive(size_t _n, uint& _code1Count) {
    if (_n <= 2) { ++_code1Count; return 1; }
    
    return FibRecursive(_n - 1, _code1Count) + FibRecursive(_n - 2, _code1Count);
}

uint FibDynamic(size_t _n, uint& _code2Count) {
    std::vector<uint> seq(_n, 1);

    for (size_t i = 2; i < _n; ++i) {
        seq[i] = seq[i - 1] + seq[i - 2];
        ++_code2Count;
    }

    return seq[_n - 1];
}

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N{}; std::cin >> N;
    uint count = 0;
    FibRecursive(N, count);
    std::cout << count << ' ';

    count = 0;
    FibDynamic(N, count);
    std::cout << count;

    return 0;
}
