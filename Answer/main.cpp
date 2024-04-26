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

    int R{}; char S[21]{};
    char output[161]{};

    for (int i = 0; i < T; ++i)
    {
        std::cin >> R >> S;

        for (int j = 0; j < 21; ++j)
        {
            if ('\0' == S[j])
            {
                int eot = j * R;
                output[eot] = '\n';
                output[eot + 1] = '\0';
                break;
            }

            memset(output + (j * R), S[j], R);
        }
        std::cout << output;
    }
    return 0;
}
