#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
#include <limits>

#include <vector>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    int N, K;
    std::cin >> N >> K;
    --K;

    std::vector<int> divisors{};
    divisors.reserve(100);
    divisors.push_back(1);
    for (int i = 2; i < N; ++i)
    {
        if (0 == N % i)
        {
            divisors.push_back(i);
        }
    }
    divisors.push_back(N);

    if (K < (int)divisors.size())
    {
        std::cout << divisors[K];
    }
    else
    {
        std::cout << 0;
    }
    return 0;
}
