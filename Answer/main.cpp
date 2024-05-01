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

#include <array>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;


    std::array<int, 5> arrNum{};
    for (size_t i = 0; i < 5; ++i)
    {
        std::cin >> arrNum[i];
    }

    size_t size = arrNum.size() - 1;
    for(bool sorted = false; false == sorted;)
    {
        sorted = true;
        for (size_t i = 0; i < size; ++i)
        {
            size_t next = i + 1;
            if (arrNum[i] > arrNum[next])
            {
                std::swap(arrNum[i], arrNum[next]);
                sorted = false;
            }
        }
    }

    size_t average{};
    for (size_t i = 0; i < arrNum.size(); ++i)
    {
        average += arrNum[i];
    }
    average /= arrNum.size();

    size_t middle = arrNum.size() / 2 + arrNum.size() % 2 - 1;
    std::cout << average << '\n' << arrNum[middle];

    return 0;
}
