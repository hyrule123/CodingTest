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
struct accScore { int idx, score; };

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N{}; std::cin >> N;
    std::vector<int> scores(N);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> scores[i];
    }
    //사이즈가 2 이하일 경우 경우의 수는 하나
    if (N <= 2) {
        int sum{};
        for (size_t i = 0; i < scores.size(); ++i) {
            sum += scores[i];
        }
        std::cout << sum;
        return 0;
    }

    std::vector<int> steps(N);
    steps[0] = scores[0];

    //두번째 계단까지 최대 점수는 무조건 계단을 다 밟고오는것
    steps[1] = scores[0] + scores[1];

    //계단 2(3번째)오는법: 0 2, 1, 2 둘중 큰거
    steps[2] = std::max(scores[0], scores[1]) + scores[2];

    for (size_t i = 3; i < N; ++i) {
        //3계단을 올라왔을 때(2 + 1)
        steps[i] = steps[i - 3] + scores[i - 1];

        //2계단을 올라왔을때와 비교하고, 더 큰값을 채택
        steps[i] = std::max(steps[i], steps[i - 2]);
        steps[i] += scores[i];
    }

    std::cout << steps.back();

    return 0;
}
