﻿#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t T;
    std::cin >> T;

    unsigned char string[102]{};
    for (size_t i = (size_t)1; i <= T; ++i)
    {
        memset(string, '*', i);
        string[i] = '\n';
        string[i + 1] = '\0';
        std::cout << string;
    }

    return 0;
}
