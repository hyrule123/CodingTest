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

#include <string>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int a{}, b{}, c{};
    std::cin >> a >> b >> c;
    
    //sort
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b > c)
    {
        int temp = b;
        b = c;
        c = temp;
    }
    int abSum = a + b;

    while (true)
    {
        if (abSum > c)
        {
            std::cout << a + b + c;
            return 0;
        }
        else
        {
            --c;
        }
    }

    return 0;
}
