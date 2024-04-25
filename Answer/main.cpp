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

    unsigned int T;
    std::cin >> T;

    std::stringstream stream{};
    unsigned int A, B;
    for (unsigned int i = 0u; i < T; ++i)
    {
        std::cin >> A >> B;
        stream << A + B << "\n";
    }
    std::cout << stream.str();

    return 0;
}
