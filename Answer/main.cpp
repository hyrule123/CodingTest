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

#include <vector>

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N{}; std::cin >> N;
    std::vector<int> seq(N);
    std::cin >> seq[0];
    int maxSum = seq[0];
    for (size_t i = 1; i < N; ++i) {
        std::cin >> seq[i];
        
        //지난 연속합에 이어서 더한다. 더한 값을 쓰는것보다 새로 시작하는게 더 클경우 여기부터 연속합을 새로 시작한다.
        seq[i] = std::max(seq[i - 1] + seq[i], seq[i]);
        maxSum = std::max(seq[i], maxSum);
    }
    std::cout << maxSum;

    return 0;
}
