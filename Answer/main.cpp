#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <limits>
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    int max{};
    int index{};
    for (int i = 0; i < 9; ++i)
    {
        int num{};
        std::cin >> num;
        if (max < num)
        {
            max = num;
            index = i + 1; 
        }
    }
    std::cout << max << "\n" << index;

    return 0;
}
