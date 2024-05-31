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

    size_t N{}; std::cin >> N; ;
    if (N == 1) { std::cout << 0; return 0; }
    else if (N <= 3) { std::cout << 1; return 0; }

    std::vector<uint> memo(N + 1);
    
    //1 to 1 -> 0, 2 to 1 -> 1, 3 to 1 -> 1
    //4 to 1부터는 3가지 경우의수를 가진다.
    
    //ex)4 to 1
    //(4-1)==3 to 1 : 1 + 1(-1 했으므로)
    //(4/2)==2 to 1 : 1 + 1(/2 했으므로)
    //(4/3): 없음
    //>> -1번째, /2번째(나누어떨어질 경우), /3번째(나누떨어질 경우)
    //인덱스에서 + 1을 한 결과와 같음

    //ex)6 to 1
    //6 - 1 to 1 + 1
    //6 / 2 to 1 + 1
    //6 / 3 to 1 + 1
    //셋중 최솟값을 찾는다

    memo[1] = 0; memo[2] = 1; memo[3] = 1;
    for (size_t i = 4; i <= N; ++i) {
        //-1
        memo[i] = memo[i - 1] + 1;

        // /2
        if (i % 2 == 0) {
            memo[i] = std::min(memo[i], memo[i / 2] + 1);
        }
        // /3
        if (i % 3 == 0) {
            memo[i] = std::min(memo[i], memo[i / 3] + 1);
        }
    }
    std::cout << memo.back();

    return 0;
}
