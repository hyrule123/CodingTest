#ifndef LOCAL
#define PAUSE (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //LOCAL

#include <iostream>

int N{};
int arrI[10]{};

int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    std::cin >> N;
    std::cout << N << "\n";

    for (int i = 0; i < N; ++i)
    {
        std::cin >> arrI[i];
    }

    for (int i = 0; i < N; ++i)
    {
        std::cout << arrI[i] << "\n";
    }

    PAUSE;
    return 0;
}
