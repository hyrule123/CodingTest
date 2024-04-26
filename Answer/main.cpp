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

    bool remainders[42] = {};

    int diffCount{};
    for (int i = 0; i < 10; ++i)
    {
        unsigned int num{};
        std::cin >> num;
        num %= 42;

        if (remainders[num] == false)
        {
            remainders[num] = true;
            ++diffCount;
        }
    }

    std::cout << diffCount;
    
    
    return 0;
}
