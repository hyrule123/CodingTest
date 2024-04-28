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

#include <array>
#include <string>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    std::array<std::string, 5> lines{};
    size_t longestLength{};
    for (size_t i = 0; i < lines.size(); ++i)
    {
        std::cin >> lines[i];

        longestLength = std::max(longestLength, lines[i].size());
    }

    for (size_t c = 0; c < longestLength; ++c)
    {
        for (size_t r = 0; r < lines.size(); ++r)
        {
            if (c < lines[r].size())
            {
                std::cout << lines[r][c];
            }
        }
    }

    return 0;
}
