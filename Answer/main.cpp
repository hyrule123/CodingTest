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

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    std::string input{};
    std::getline(std::cin, input);

    char A[4]{}, B[4]{};
    bool isA_Bigger{};
    for (int i = 0; i < 3; ++i)
    {
        A[i] = input[2 - i];
        B[i] = input[6 - i];


        if (false == isA_Bigger && A[i] > B[i])
        {
            isA_Bigger = true;
        }
    }

    if (isA_Bigger)
    {
        std::cout << A;
    }
    else
    {
        std::cout << B;
    }
    return 0;
}
