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
#include <array>

inline char CharToIndex(char _c)
{
    constexpr char toUpper = 'a' - 'A';

    if ('a' <= _c)
    {
        _c -= toUpper;
    }
    
    return (_c - 'A');
}
inline char IndexToChar(int _i)
{
    return ((char)_i + 'A');
}


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    std::array<int, 26> usedCount{};

    std::string inputStr{};
    inputStr.reserve(1000001);
    std::cin >> inputStr;

    for (size_t i = 0; i < inputStr.size(); ++i)
    {
        ++usedCount[CharToIndex(inputStr[i])];   
    }

    
    int mostUsedIdx{};
    bool redundantSame{};
    for (size_t i = 1; i < usedCount.size(); ++i)
    {
        if (usedCount[i] > usedCount[mostUsedIdx])
        {
            mostUsedIdx = (int)i;
            redundantSame = false;
        }
        else if (usedCount[i] == usedCount[mostUsedIdx])
        {
            redundantSame = true;
        }
    }

    std::cout << (redundantSame ? '?' : IndexToChar(mostUsedIdx));

    return 0;
}
