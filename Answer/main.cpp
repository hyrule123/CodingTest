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

    size_t N{};
    std::cin >> N;

    //각 원소의 최대 크기가 10000 이하 자연수라는게 키포인트
    //10001개짜리 배열(0 ~ 10000 = 10001개)을 만들고 원소 개수만 기록해둔 뒤 개수만큼 출력해주면 된다.

    //4 * 10001 = 40004 bytes(<8192kb 제한)
    std::vector<unsigned int> counter{};
    counter.resize(10001);

    for (size_t i = 0; i < N; ++i)
    {
        unsigned int input{};
        std::cin >> input;
        ++(counter[input]);
    }

    for (size_t i = 0; i < counter.size(); ++i)
    {
        for (unsigned int j = 0; j < counter[i]; ++j)
        {
            std::cout << i << '\n';
        }
    }

    return 0;
}
