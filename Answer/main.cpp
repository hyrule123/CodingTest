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

    using namespace std;

    int T{};
    std::cin >> T;

    char S[1001];
    for (int i = 0; i < T; ++i)
    {
        std::cin >> S;
        std::cout << S[0];

        for(int i = 0; i < 1001; ++i)
        {
            if ('\0' == S[i])
            {
                std::cout << S[i - 1] << "\n";
                break;
            }
        }
    }
    
    return 0;
}
