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

    std::vector<int> divisors{};
    divisors.reserve(100);
    while (true)
    {
        int n{};
        std::cin >> n;
        if (-1 == n)
        {
            break;
        }

        divisors.clear();
        divisors.push_back(1);
        for (int i = 2; i < n; ++i)
        {
            if (0 == n % i)
            {
                divisors.push_back(i);
            }
        }

        int sumDivisor{};
        for (size_t i = 0; i < divisors.size(); ++i)
        {
            sumDivisor += divisors[i];
        }

        if (sumDivisor == n)
        {
            std::cout << n << " = ";

            size_t end = divisors.size() - 1;
            for (size_t i = 0; i <= end; ++i)
            {
                std::cout << divisors[i];
                if (i != end)
                {
                    std::cout << " + ";
                }
                else
                {
                    std::cout << "\n";
                }
            }
        }
        else
        {
            std::cout << n << " is NOT perfect.\n";
        }
    }
    return 0;
}
