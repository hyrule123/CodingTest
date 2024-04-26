#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    int N{}, M{};
    std::cin >> N >> M;

    int* basket = new int[N];
    memset(basket, 0, sizeof(int) * N);

    for (int count = 0; count < M; ++count)
    {
        int i{}, j{}, k{};
        std::cin >> i >> j >> k;
        --i; --j;

        for (i; i <= j; ++i)
        {
            basket[i] = k;
        }
    }

    for (int count = 0; count < N; ++count)
    {
        std::cout << basket[count] << " ";
    }

    delete[] basket;
    return 0;
}
