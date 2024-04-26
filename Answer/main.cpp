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
#include <sstream>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    std::string line{};
    std::getline(std::cin, line);

    size_t reverseCount = line.size() / (size_t)2;
    for (size_t l = 0; l < reverseCount; ++l)
    {
        char temp = line[l];
        size_t r = line.size() - 1 - l;
        line[l] = line[r];
        line[r] = temp;
    }

    std::stringstream stream{ line };
    int A{}, B{};
    stream >> B >> A;
    
    std::cout << (A > B ? A : B);

    return 0;
}
