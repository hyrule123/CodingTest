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
    
    //계차수열: 1 2 3 4 ...
    //변 하나의 길이 1, 단계 x라고 하면
    //위, 아래: 2 * x
    //좌, 우: 2 * x
    //4 * x

    std::uint64_t n{};
    std::cin >> n;
    std::cout << (std::uint64_t)4 * n;
    return 0;
}
