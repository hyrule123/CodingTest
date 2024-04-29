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

    int loopSize = N;
    for (int i = 2; i * i <= loopSize; ++i)
    {
        //나눠떨어질 경우에는 소인수이다.
        while (0 == N % i)
        {
            N /= i;
            std::cout << i << '\n';
        }

        if (1 == N)
        {
            break;
        }
    }

    //1이 아닌 값이남아있을 경우 이것까지 출력
    if (N != 1)
    {
        std::cout << N;
    }

    return 0;
}
