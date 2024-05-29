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
using uint = unsigned int;
using cost = std::array<uint, 3>;
enum { r, g, b };

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N{}; std::cin >> N;
    cost prevCost{}, curCost{};
    std::cin >> prevCost[r] >> prevCost[g] >> prevCost[b];
    for (size_t i = 1; i < N; ++i) {
        std::cin >> curCost[r] >> curCost[g] >> curCost[b];
        
        //r로 넘어갈 수 있는 색상 = g, b >> g, b중 코스트가 적은 쪽을 선택한다.
        curCost[r] += std::min(prevCost[g], prevCost[b]);
        curCost[g] += std::min(prevCost[r], prevCost[b]);
        curCost[b] += std::min(prevCost[r], prevCost[g]);

        prevCost = curCost;
    }
    
    std::cout << std::min(std::min(curCost[r], curCost[g]), curCost[b]);

    return 0;
}
