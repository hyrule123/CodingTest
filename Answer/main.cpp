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

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N{}; std::cin >> N;
    std::vector<uint> prev, cur; prev.reserve(N); cur.reserve(N);
    
    prev.resize(1); std::cin >> prev[0];
    for (size_t i = 2; i <= N; ++i) {
        cur.resize(i);

        //맨앞에껀 좌측이 없으므로 선택지는 1개
        std::cin >> cur.front();
        cur.front() += prev.front();
        for (size_t j = 1, jEnd = cur.size() - 1; j < jEnd; ++j) {
            std::cin >> cur[j];
            //j번째 선택지가 가질수 있는 선택지 중 큰걸 골라준다.
            cur[j] += std::max(prev[j - 1], prev[j]);
        }
        //맨뒤에껏도 마찬가지로 선택지 1개
        std::cin >> cur.back();
        cur.back() += prev.back();

        //prev와 cur을 교체
        prev.swap(cur);
    }

    //모든 최대값 선택지 중 제일 큰걸 찾는다.
    uint maxVal = prev[0];
    for (size_t i = 1; i < prev.size(); ++i) {
        if (maxVal < prev[i]) { maxVal = prev[i]; }
    }
    std::cout << maxVal;

    return 0;
}
