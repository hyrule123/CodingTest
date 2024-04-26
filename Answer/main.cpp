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
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    unsigned int N;
    int X;
    std::cin >> N >> X;

    for (unsigned int i = 0u; i < N; ++i)
    {
        int num;
        std::cin >> num;
        if (num < X)
        {
            std::cout << num << " ";
        }
    }

    return 0;
}
