#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int A{}, B{};

    while (std::cin >> A >> B)
    {
        std::cout << A + B << "\n";
    }

    return 0;
}
