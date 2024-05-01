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


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{};
    std::cin >> N;

    //최소 갯수를 구해야하니까 3키로짜린 최대한 적고 5키로짜린 많아야함
    for (int x = 0; x <= N; ++x)
    {
        int _3x = 3 * x;
        //5키로짜린 많아야하므로 역순으로 계산
        for (int y = N / 5 ; y >= 0; --y)
        {
            int _5y = 5 * y;

            int _3x_5y = _3x + _5y;
            if (N == _3x_5y)
            {
                std::cout << x + y;
                return 0;
            }
            //y는 계속 줄어드므로 N보다 작아지면 더이상 이번루프에서 근이 안나옴
            else if (N > _3x_5y)
            {
                break;
            }
        }
    }
    std::cout << -1;

    return 0;
}
