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

#include <bitset>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    std::bitset<32> attendance{};

    for (int i = 1; i <= 28; ++i)
    {
        int num{};
        std::cin >> num;
        attendance[num] = true;
    }

    for (int i = 1; i <= 30; ++i)
    {
        if (false == attendance[i])
        {
            std::cout << i << "\n";
        }
    }

    
    return 0;
}
