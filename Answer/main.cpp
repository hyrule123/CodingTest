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

    int N{}, M{};
    std::cin >> N >> M;

    std::vector<int> baskets((size_t)N);

    for (size_t i = 0; i < baskets.size(); ++i)
    {
        baskets[i] = (int)i + 1;
    }

    for (int c = 0; c < M; ++c)
    {
        int i{}, j{};
        std::cin >> i >> j;
        --i; --j;
        int temp = baskets[i];
        baskets[i] = baskets[j];
        baskets[j] = temp;
    }

    for (size_t i = 0; i < baskets.size(); ++i)
    {
        std::cout << baskets[i] << " ";
    }

    
    return 0;
}
