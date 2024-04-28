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

    using namespace std;
    
    
    int maxNum{std::numeric_limits<int>::min()};
    int X{};
    int Y{};

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            int input{};
            std::cin >> input;

            if (maxNum < input)
            {
                maxNum = input;
                X = i;
                Y = j;
            }
        }
    }

    std::cout << maxNum << '\n' << X + 1 << ' ' << Y + 1;

    return 0;
}
