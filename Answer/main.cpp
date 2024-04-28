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

    int A, B;
    
    
    while (true)
    {
        std::cin >> A >> B;
        if (0 == A && 0 == B)
        {
            break;
        }

        int idx = -1;
        if (A < B)
        {
            if (B % A == 0)
            {
                idx = 0;
            }
            else
            {
                idx = 2;
            }
        }
        else
        {
            if (A % B == 0)
            {
                idx = 1;
            }
            else
            {
                idx = 2;
            }
        }

        constexpr const std::string_view output[] = { "factor\n", "multiple\n", "neither\n" };
        std::cout << output[idx];
    }


    return 0;
}
