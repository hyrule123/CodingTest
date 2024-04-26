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

    constexpr int alphabet2Time[] =
    { 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10 };

    char S[16]{};
    std::cin >> S;

    int sumTime{};
    for (int i = 0; i < 16; ++i)
    {
        if ('\0' == S[i])
        {
            break;
        }

        //A == 65
        sumTime += alphabet2Time[S[i] - 65];
    }

    std::cout << sumTime;

    return 0;
}
