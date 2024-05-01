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

    int a{}, b{}, c{}, d{}, e{}, f{};
    std::cin >> a >> b >> c >> d >> e >> f;

    for (int x = -999; x <= 999; ++x)
    {
        for (int y = -999; y <= 999; ++y)
        {
            if (c == a * x + b * y && f == d * x + e * y)
            {
                std::cout << x << ' ' << y;
                return 0;
            }
        }
    }


    return 0;
}
