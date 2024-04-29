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

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{};
    std::cin >> N;
    
    constexpr int intMin{ std::numeric_limits<int>::min() };
    constexpr int intMax{ std::numeric_limits<int>::max() };
    
    int l{ intMax }, b{ intMax }, r{ intMin }, t{ intMin };
    for (int i = 0; i < N; ++i)
    {
        int x{}, y{};
        std::cin >> x >> y;
        
        l = std::min(x, l);
        r = std::max(x, r);

        b = std::min(y, b);
        t = std::max(y, t);
    }

    std::cout << std::labs(r - l) * std::labs(t - b);

    return 0;
}
