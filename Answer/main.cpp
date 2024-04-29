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
    
    int x1{}, x2{}, x3{}, y1{}, y2{}, y3{};
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int printX{};
    if (x1 == x2)
    {
        printX = x3;
    }
    else if (x1 == x3)
    {
        printX = x2;
    }
    else
    {
        printX = x1;
    }

    int printY{};
    if (y1 == y2)
    {
        printY = y3;
    }
    else if (y1 == y3)
    {
        printY = y2;
    }
    else
    {
        printY = y1;
    }

    std::cout << printX << ' ' << printY;
    return 0;
}
