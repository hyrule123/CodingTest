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

#include <array>
using uint64 = std::uint64_t;
constexpr size_t size = 100;
constexpr std::array<uint64, size> PadovanPreMake() {
    std::array<uint64, size> ret{ 1, 1, 1, 2, 2, };

    for (size_t i = 5; i < size; ++i) {
        ret[i] = ret[i - 1] + ret[i - 5];
    }

    return ret;
}
constexpr std::array<uint64, size> PadovanSeq = PadovanPreMake();

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    int N; std::cin >> N;
    for (int i = 0; i < N; ++i) {
        size_t T; std::cin >> T;
        std::cout << PadovanSeq[T - 1] << '\n';
    }

    return 0;
}
