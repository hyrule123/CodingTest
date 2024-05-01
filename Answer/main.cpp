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

#include <vector>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t size{};
    std::cin >> size;

    std::vector<int> arrNum{};
    arrNum.resize(size);
    for (size_t i = 0; i < size; ++i)
    {
        std::cin >> arrNum[i];
    }

    --size;
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

    for (size_t i = 0; i < arrNum.size(); ++i)
    {
        std::cout << arrNum[i] << '\n';
    }

    return 0;
}
