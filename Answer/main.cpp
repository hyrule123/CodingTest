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

    std::vector<int> baskets{};
    baskets.resize(N);
    for (size_t i = 0; i < baskets.size(); ++i)
    {
        baskets[i] = (int)i + 1;
    }

    for (int c = 0; c < M; ++c)
    {
        int i{}, j{};
        std::cin >> i >> j;
        --i; --j;

        int swapCount = (j - i + 1) / 2;
        for (int d = 0; d < swapCount; ++d)
        {
            int left = i + d;
            int right = j - d;
            int temp = baskets[left];
            baskets[left] = baskets[right];
            baskets[right] = temp;
        }
    }

    for (size_t i = 0; i < baskets.size(); ++i)
    {
        std::cout << baskets[i] << " ";
    }
    
    
    return 0;
}
