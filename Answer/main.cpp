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

/*
* 백준 질문게시판 발췌
길이가 k인 경우는 길이가 k-2에서 00를 더한 경우 +
길이가 k-1에서 1을 더한 경우의 합으로 볼 수 있기 때문에

dp[1]=1,dp[2]=2로 두고 dp[k]=dp[k-1]+dp[k-2] 으로 점화식을 세워서 나타내면 피보나치 수열과 같게 됩니다
*/
#include <vector>
using uint = unsigned int;
uint Fib15746(size_t _n) {
    std::vector<uint> Fib(_n + 1, 1);
    
    for (size_t i = 2; i <= _n; ++i) {
        Fib[i] = (Fib[i - 1] + Fib[i - 2]) % 15746;
    }

    return Fib.back();
}

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    size_t N; std::cin >> N;
    std::cout << Fib15746(N);

    return 0;
}
