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

    int T{};
    std::cin >> T;

    constexpr int changes[] = { 25, 10, 5, 1 };
    constexpr int numChanges = sizeof(changes) / sizeof(int);

    for (int c = 0; c < T; ++c)
    {
        int cents{};
        std::cin >> cents;

        for (int i = 0; i < numChanges; ++i)
        {
            int change = cents / changes[i];
            cents -= change * changes[i];
            std::cout << change << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
