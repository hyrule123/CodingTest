#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint = unsigned int;
uint mod = 1'000'000'000;

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    uint N{}; std::cin >> N;
    if (N == 1) { std::cout << 9; return 0; }

    //1자리수일 경우의 값(0부터 각 자리수별로 1개씩, "0 포함" -> 마지막 합산에서만 뺄것임)
    //ex)1자리수 0 -> 2자리수 10이 됨
    std::vector<uint> prev({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });
    std::vector<uint> cur((size_t)10);

    for (uint i = 2; i <= N; ++i) {
        //이전 단계에서 1로 시작했던 숫자에만 0을 붙일 수 있다
        cur[0] = prev[1] % mod;
        //이전 단계에서 8로 시작했던 숫자에만 9를 붙일 수 있다.
        cur[9] = prev[8] % mod;

        //이번 단계의 j로 시작하는 수의 뒤에는 j-1, j+1만 붙일 수 있다.
        //ex)2_1..., 2_3...
        for (uint j = 1; j <= 8; ++j) {
            cur[j] = (prev[j - 1] + prev[j + 1]) % mod;
        }
        cur.swap(prev);
    }

    uint sum{};
    for (uint i = 1; i <= 9; ++i) {
        sum += prev[i];
        sum %= mod;
    }
    std::cout << sum;

    return 0;
}
