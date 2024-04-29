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

    constexpr std::string_view answers[]{ "Scalene", "Isosceles", "Equilateral" };

    int lines[3]{};
    for (int i = 0; i < 3; ++i)
    {
        std::cin >> lines[i];
    }

    if (180 != (lines[0] + lines[1] + lines[2]))
    {
        std::cout << "Error";
        return 0;
    }

    //for문으로 하는건 별론듯
    int sameCount{};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i + 1; j < 3; ++j)
        {
            if (lines[i] == lines[j])
            {
                ++sameCount;
            }
        }
        if (2 <= sameCount)
        {
            break;
        }
    }
    std::cout << answers[sameCount];

    return 0;
}
