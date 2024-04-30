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

    std::int64_t N{}, M{};
    std::cin >> N >> M;

    std::vector<std::int64_t> cards{};
    cards.resize(N);
    for (size_t i = 0; i < cards.size(); ++i)
    {
        std::cin >> cards[i];
    }

    std::int64_t nearest{ std::numeric_limits<std::int64_t>::max() };

    const size_t iEnd = cards.size() - (size_t)2;
    const size_t jEnd = cards.size() - (size_t)1;
    for (size_t i = 0; i < iEnd; ++i)
    {
        for (size_t j = i + 1; j < jEnd; ++j)
        {
            for (size_t k = j + 1; k < cards.size(); ++k)
            {
                std::int64_t dist = M - (cards[i] + cards[j] + cards[k]);
                if (0 <= dist && dist < nearest)
                {
                    nearest = dist;
                }
            }
        }
    }
    std::cout << M - nearest;

    return 0;
}
