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
#include <array>


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    constexpr const std::string_view croatian[] =
    {
        "c=", "c-", "d-", "dz=", "lj", "nj", "s=", "z="
    };
    size_t arrSize = sizeof(croatian) / sizeof(std::string_view);

    char input[103]{};
    std::cin >> input;
    size_t slen = std::strlen(input);

    size_t croatianCharCount{};
    for (size_t i = 0; i < slen; ++i)
    {
        for (size_t j = 0; j < arrSize; ++j)
        {
            bool found = true;

            for (size_t k = 0; k < croatian[j].size(); ++k)
            {
                if (input[i + k] != croatian[j][k])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                i += croatian[j].size() - 1;
                break;
            }
        }

        ++croatianCharCount;
    }


    std::cout << croatianCharCount;
    return 0;
}
