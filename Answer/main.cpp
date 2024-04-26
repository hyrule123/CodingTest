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

    int N{};
    std::cin >> N;
    std::cin.get();
    
    int sum{};
    for (int i = 0; i < N; ++i)
    {
        char c{};
        std::cin >> c;

        //ASCII code 0 == 48
        sum += c - 48;
    }
    
    std::cout << sum;
    
    return 0;
}
