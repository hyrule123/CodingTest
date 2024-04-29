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

    while (true)
    {
        //c가 제일 길게 해주기
        int a{}, b{}, c{};
        std::cin >> a >> b >> c;
        if (0 == a && 0 == b && 0 == c)
        {
            break;
        }

        //sort
        if(a > b)
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

        if ((a + b) <= c)
        {
            std::cout << "Invalid\n";
        }

        else if (a == b && b == c)
        {
            std::cout << "Equilateral\n";
        }
        else if (a == b || b == c || a == c)
        {
            std::cout << "Isosceles\n";
        }
        else
        {
            std::cout << "Scalene\n";
        }
    }
    return 0;
}
